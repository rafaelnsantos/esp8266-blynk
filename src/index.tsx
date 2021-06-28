import './style/index.css';

import { FunctionalComponent, h } from 'preact';
import Home from '~/components/home';
import Header from '~/components/header';
import { SocketProvider } from './providers/SocketProvider';
import { setup } from 'goober';

setup(h);

const App: FunctionalComponent = () => {
  return (
    <div id="app">
      <SocketProvider url="ws://192.168.4.1:81/">
        <Header />
        <Home />
      </SocketProvider>
    </div>
  );
};

export default App;
