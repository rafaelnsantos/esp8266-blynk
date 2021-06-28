import { AnimatePresence } from 'framer-motion';
import { styled } from 'goober';
import { FunctionalComponent, h } from 'preact';
import { useCallback, useState } from 'preact/hooks';
import Step1 from '~/components/step1';
import Step2 from '~/components/step2';
import Step3 from '~/components/step3';
import { Connection } from '~/providers/SocketProvider';

const Container = styled('section')`
  display: flex;
  flex: 1;
  flex-direction: column;
  padding: 0 5px;
`;

const Home: FunctionalComponent = () => {
  const [ssid, setSSID] = useState('');
  const [step, setStep] = useState(1);
  const [connections, setConnections] = useState<Connection[]>([]);

  const handlePickSSID = (SSID: string) => {
    setSSID(SSID);
    setStep((current) => current + 1);
  };

  const handleBack = useCallback(() => setStep((current) => current - 1), []);

  const goToNextStep = useCallback(() => setStep((current) => current + 1), []);

  return (
    <Container>
      <AnimatePresence exitBeforeEnter initial={false}>
        {step === 1 && <Step1 key="step1" onClick={handlePickSSID} connections={connections} onScan={setConnections} />}

        {step === 2 && <Step2 key="step2" onBack={handleBack} onSuccess={goToNextStep} ssid={ssid} />}

        {step === 3 && <Step3 key="step3" onSuccess={goToNextStep} ssid={ssid} />}
      </AnimatePresence>
    </Container>
  );
};

export default Home;
