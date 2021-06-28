import { useCallback, useEffect, useRef, useState } from 'preact/hooks';

export interface Connections {
  [key: string]: {
    signal: number;
    encryption: number;
  };
}

export interface BlynkAuth {
  auth: string;
}

export interface WiFiCredentials {
  ssid: string;
  pass?: string;
}

interface WebSocketMessages {
  onWiFiMessage: (message: { status: boolean }) => void;
  onAuthMessage: (message: { status: boolean }) => void;
  onConnectionsReceived: (message: Connections) => void;
}

export function useWebsocket(config: WebSocketMessages) {
  const connection = useRef<WebSocket>();
  const [connected, setConnected] = useState(false);

  const sendAuth = useCallback(
    (auth: BlynkAuth) => {
      console.log(auth);
      connection.current.send(JSON.stringify({ ...auth, type: 'auth' }));
    },
    [connection]
  );

  const tryCredentials = useCallback((credentials: WiFiCredentials) => {
    console.log(credentials);
    connection.current.send(JSON.stringify({ ...credentials, type: 'wifi' }));
  }, []);

  const requestScan = useCallback(() => {
    console.log('request scan');
    connection.current.send(JSON.stringify({ type: 'scan' }));
  }, []);

  const connect = useCallback(() => {
    connection.current = new WebSocket('ws://192.168.4.1:81/');

    connection.current.onopen = function () {
      console.log('WebSocket connected');
      setConnected(true);
    };

    connection.current.onerror = function (error) {
      console.log('WebSocket Error ', error);
    };

    connection.current.onclose = function () {
      console.log('WebSocket closed');
      setConnected(false);
    };
  }, []);

  useEffect(() => {
    connect();

    return () => {
      connection.current.close();
    };
  }, [connect]);

  useEffect(() => {
    connection.current.onmessage = function (message) {
      const { type, ...data } = JSON.parse(message.data);
      console.log(data);
      switch (type) {
        case 'scan':
          config.onConnectionsReceived(data);
          break;

        case 'wifi':
          config.onWiFiMessage(data);
          break;

        case 'auth':
          config.onAuthMessage(data);
          break;

        default:
          console.log('missing message type');
      }

      if (data.type === 'connections') {
      }
    };
  }, [connection, config]);

  useEffect(() => {
    if (!connected) connect();
  }, [connected, connect]);

  return { sendAuth, tryCredentials, requestScan, connected };
}
