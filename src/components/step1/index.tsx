import { motion } from 'framer-motion';
import { styled } from 'goober';
import { FunctionalComponent, h } from 'preact';
import { Connection as ConnectionType } from '~/providers/SocketProvider';
import Connection from '../connection';
import ScanButton from '../scan';

interface ConnectionProps {
  onClick: (ssid: string) => void;
  onScan: (connections: ConnectionType[]) => void;
  connections: ConnectionType[];
}

const Container = styled(motion.div)`
  display: flex;
  flex-direction: column;
  flex: 1;
  justify-content: space-between;
`;

const DivConnections = styled('div')`
  display: flex;
  flex-direction: column;
`;

const Step1: FunctionalComponent<ConnectionProps> = (props) => {
  return (
    <Container
      initial={{ opacity: 0 }}
      animate={{ opacity: 1 }}
      exit={{ opacity: 0, x: 300 }}
      id="step-1"
      transition="easeIn"
    >
      <DivConnections>
        {props.connections.map(({ name, signal, encryption }) => (
          <Connection key={name} name={name} signal={signal} encrypted={encryption} onClick={props.onClick} />
        ))}
      </DivConnections>

      <ScanButton onScanComplete={props.onScan} />
    </Container>
  );
};

export default Step1;
