import { motion } from 'framer-motion';
import { styled } from 'goober';
import { Fragment, FunctionalComponent, h } from 'preact';
import { StateUpdater, useCallback, useState } from 'preact/hooks';
import { useWebsocket } from '~/providers/SocketProvider';
import Button from '../atoms/Button';
import Loading from '../loading';

interface Step2Props {
  onSuccess: () => void;
  onBack: () => void;
  ssid: string;
}

const Container = styled(motion.div)`
  display: flex;
  flex-direction: column;
  flex: 1;
`;

const ContainerForm = styled('form')`
  display: flex;
  flex-direction: column;
  flex: 1;
  justify-content: center;
`;

const ButtonContainer = styled('div')`
  display: flex;
  flex-direction: row;
  justify-content: flex-end;
`;

const StyledButton = styled(Button)`
  padding: 10px 20px;
  margin-left: 15px;
  cursor: pointer;
`;

const Step2: FunctionalComponent<Step2Props> = ({ onSuccess, ssid, onBack }) => {
  const [testingCredentials, setTestingCredentials] = useState(false);
  const [passwordError, setPasswordError] = useState(false);
  const [pass, setPass] = useState('');

  const onWiFiMessage = useCallback(
    ({ status }: any) => {
      if (status) {
        onSuccess();
      } else {
        setPasswordError(true);
        setTestingCredentials(false);
      }
    },
    [onSuccess]
  );

  const { tryCredentials, connected } = useWebsocket({
    onWiFiMessage
  });

  const handleSubmitPassword = (e: any) => {
    e.preventDefault();

    tryCredentials({ ssid, pass });
    setPasswordError(false);
    setTestingCredentials(true);
  };

  const handleInput = useCallback(
    (setter: StateUpdater<string>) => (e: h.JSX.TargetedEvent<HTMLInputElement, Event>) =>
      setter(e.currentTarget.value),
    []
  );

  return (
    <Container initial={{ opacity: 0 }} animate={{ opacity: 1 }} exit={{ opacity: 0 }} id="step-2">
      <Fragment>
        {testingCredentials ? (
          <Loading />
        ) : (
          <ContainerForm onSubmit={handleSubmitPassword}>
            <div>Password for {ssid}</div>
            <input style={{ margin: '10px 0 20px 0' }} value={pass} type="text" onInput={handleInput(setPass)} />
            <ButtonContainer>
              <StyledButton
                style={{ backgroundColor: 'white', color: 'rgb(88, 88, 88)', boxShadow: 'none' }}
                type="button"
                onClick={onBack}
              >
                back
              </StyledButton>
              <StyledButton type="submit" disabled={!connected}>
                Confirm
              </StyledButton>
            </ButtonContainer>
            {passwordError && <div>Check password</div>}
          </ContainerForm>
        )}
      </Fragment>
    </Container>
  );
};

export default Step2;
