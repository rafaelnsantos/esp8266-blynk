import { FunctionalComponent, h } from 'preact';
import { useCallback } from 'preact/hooks';
import { Lock, Wifi } from 'preact-feather';
import { styled } from 'goober';
import { motion } from 'framer-motion';

interface ConnectionProps {
  name: string;
  signal: number;
  encrypted: boolean;

  onClick: (ssid: string) => void;
}

const StyledButton = styled(motion.button)`
  border: none;
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 15px;
  margin: 15px 0 0 0;
  background: rgb(197 197 197);
  border-radius: 10px;
  box-shadow: 0 0 20px 8px #d0d0d0;
  cursor: pointer;
`;

const item = {
  hidden: { opacity: 0 },
  show: { opacity: 1 }
};

const Connection: FunctionalComponent<ConnectionProps> = (props) => {
  const onClick = useCallback(() => props.onClick(props.name), [props]);
  // todo change wifi icon depending on signal strengh
  return (
    <StyledButton variants={item} id={props.name} initial="hidden" animate="show" onClick={onClick}>
      <Wifi size={19} />
      <div style={{ display: 'flex', flex: 1, marginLeft: 10 }}>{props.name}</div>
      {props.encrypted && <Lock size={19} />}
    </StyledButton>
  );
};

export default Connection;
