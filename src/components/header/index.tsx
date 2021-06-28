import { FunctionalComponent, h } from 'preact';
import { useWebsocket } from '~/providers/SocketProvider';
import { ZapOff, Zap } from 'preact-feather';
import { styled } from 'goober';

const Icon = styled(ZapOff)`
  @keyframes pulse {
    0% {
      opacity: 0.3;
    }
    50% {
      opacity: 1;
    }
    100% {
      opacity: 0.3;
    }
  }

  animation: pulse 1s infinite ease-in-out;
`;

const Container = styled('header')`
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 0 25px;
`;

const Header: FunctionalComponent = () => {
  const { connected, connect } = useWebsocket({});

  return (
    <Container>
      <h1>Preact App</h1>
      {connected ? <Zap color="#00ff00" /> : <Icon onClick={connect} color="#ff0000" />}
    </Container>
  );
};

export default Header;
