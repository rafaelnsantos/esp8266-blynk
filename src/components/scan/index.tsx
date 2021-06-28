import { styled } from 'goober';
import { Fragment, FunctionalComponent, h } from 'preact';
import { useCallback, useState } from 'preact/hooks';
import { Connection, useWebsocket } from '~/providers/SocketProvider';
import Loading from '../loading';
import { Search } from 'preact-feather';
import Button from '../atoms/Button';

interface ScanButtonProps {
  onScanComplete: (connections: Connection[]) => void;
}

const StyledButton = styled(Button)`
  display: flex;
  flex-direction: column;
  align-items: center;
  width: 75px;
  align-self: flex-end;
  border-radius: 75px;
  height: 75px;
  justify-content: center;
  margin: 15px;
`;

const ScanButton: FunctionalComponent<ScanButtonProps> = ({ onScanComplete }) => {
  const [scanning, setScanning] = useState(false);

  const onConnectionsReceived = useCallback(
    (connections: Connection[]) => {
      onScanComplete(connections);

      setScanning(false);
    },
    [onScanComplete]
  );

  const { requestScan, connected } = useWebsocket({
    onConnectionsReceived
  });

  const handleScan = useCallback(() => {
    requestScan();
    onScanComplete([]);
    setScanning(true);
  }, [requestScan, onScanComplete]);

  return (
    <Fragment>
      {scanning && <Loading />}
      <StyledButton id="scan" onClick={handleScan} disabled={scanning || !connected}>
        <Search />
        <div>Scan</div>
      </StyledButton>
    </Fragment>
  );
};

export default ScanButton;
