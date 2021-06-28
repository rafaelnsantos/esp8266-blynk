import { styled } from 'goober';
import { FunctionalComponent, h } from 'preact';
import { StateUpdater, useCallback, useState } from 'preact/hooks';
import { useWebsocket } from '~/providers/SocketProvider';

interface ConnectionProps {
  onSuccess: () => void;
  ssid: string;
}

const Container = styled('form')`
  display: flex;
  flex-direction: column;
  flex: 1;
  justify-content: space-evenly;
`;

const Step3: FunctionalComponent<ConnectionProps> = ({ onSuccess, ssid }) => {
  const [auth, setAuth] = useState('');

  const onAuthMessage = useCallback(
    ({ status }: any) => {
      console.log('auth', status);
      if (status) onSuccess();
    },
    [onSuccess]
  );

  const { sendAuth, connected } = useWebsocket({
    onAuthMessage
  });

  const handleInput = useCallback(
    (setter: StateUpdater<string>) => (e: h.JSX.TargetedEvent<HTMLInputElement, Event>) =>
      setter(e.currentTarget.value),
    []
  );

  const handleSubmitAuth = useCallback(
    (e: any) => {
      e.preventDefault();
      sendAuth({
        auth
      });
    },
    [sendAuth, auth]
  );

  return (
    <Container id="step-3" onSubmit={handleSubmitAuth}>
      Connected to {ssid}
      <div>
        Blynk Token: <input value={auth} type="text" onInput={handleInput(setAuth)} />
      </div>
      <button type="submit" disabled={!connected}>
        Confirm
      </button>
    </Container>
  );
};

export default Step3;
