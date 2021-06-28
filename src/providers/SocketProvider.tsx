import { createContext, FunctionalComponent, h } from 'preact';
import { useCallback, useContext, useEffect, useRef, useState } from 'preact/hooks';

interface SocketContextValues {
  connected: boolean;
  socket?: WebSocket;
  connect?: () => void;
}

const SocketContext = createContext<SocketContextValues>({
  connected: false
});

export interface Connection {
  name: string;
  signal: number;
  encryption: boolean;
}

export interface BlynkAuth {
  auth: string;
}

export interface WiFiCredentials {
  ssid: string;
  pass?: string;
}

export interface WebSocketMessages {
  onWiFiMessage?: (message: { status: boolean }) => void;
  onAuthMessage?: (message: { status: boolean }) => void;
  onConnectionsReceived?: (message: Connection[]) => void;
}

export const useWebsocket = ({ onAuthMessage, onConnectionsReceived, onWiFiMessage }: WebSocketMessages) => {
  const { connected, socket, connect } = useContext(SocketContext);

  const onMessageReceived = useCallback(
    (message: MessageEvent) => {
      const { type, ...data } = JSON.parse(message.data);
      console.log(type, data);
      switch (type) {
        case 'scan':
          if (onConnectionsReceived) onConnectionsReceived(data.connections);
          break;

        case 'wifi':
          if (onWiFiMessage) onWiFiMessage(data);
          break;

        case 'auth':
          if (onAuthMessage) onAuthMessage(data);
          break;

        default:
          console.log('missing message type');
      }
    },
    [onAuthMessage, onConnectionsReceived, onWiFiMessage]
  );

  const sendMessage = useCallback(
    (message: object) => {
      if (socket) {
        socket.send(JSON.stringify(message));
      } else {
        throw new Error('no socket');
      }
    },
    [socket]
  );

  const sendAuth = useCallback(
    (auth: BlynkAuth) => {
      console.log(auth);
      sendMessage({ ...auth, type: 'auth' });
    },
    [sendMessage]
  );

  const tryCredentials = useCallback(
    (credentials: WiFiCredentials) => {
      console.log(credentials);
      sendMessage({ ...credentials, type: 'wifi' });
    },
    [sendMessage]
  );

  const requestScan = useCallback(() => {
    console.log('request scan');
    sendMessage({ type: 'scan' });
  }, [sendMessage]);

  useEffect(() => {
    if (!socket) return;
    socket.addEventListener('message', onMessageReceived);

    return () => {
      socket.removeEventListener('message', onMessageReceived);
    };
  }, [socket, onMessageReceived]);

  return { connected, sendAuth, tryCredentials, requestScan, connect };
};

interface SocketProviderProps {
  url: string;
}

export const SocketProvider: FunctionalComponent<SocketProviderProps> = ({ url, children }) => {
  const connection = useRef<WebSocket>();
  const [connected, setConnected] = useState(false);

  const connect = useCallback(() => {
    connection.current = new WebSocket(url);

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
  }, [url]);

  useEffect(() => {
    if (!connected) connect();
  }, [connected, connect]);

  useEffect(() => {
    return () => {
      console.log('closing');
      connection.current.close();
    };
  }, []);

  return (
    <SocketContext.Provider value={{ connected, socket: connection.current, connect }}>
      {children}
    </SocketContext.Provider>
  );
};
