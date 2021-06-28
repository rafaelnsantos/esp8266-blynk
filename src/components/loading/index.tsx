import { styled } from 'goober';
import { FunctionalComponent, h } from 'preact';

const Cube = styled('div')<{ color: string } & h.JSX.HTMLAttributes<HTMLDivElement>>`
  &:before {
    background-color: ${(props) => props.color} !important;
  }
`;

interface LoadingColor {
  color?: string;
}

const Container = styled('div')`
  position: absolute;
  left: 0;
  right: 0;
  margin: auto;
  bottom: 0;
  top: 0;
`;

const Loading: FunctionalComponent<LoadingColor> = ({ color = 'rgb(49, 49, 49)' }) => (
  <Container className="sk-folding-cube">
    <Cube color={color} className="sk-cube1 sk-cube" />
    <Cube color={color} className="sk-cube2 sk-cube" />
    <Cube color={color} className="sk-cube4 sk-cube" />
    <Cube color={color} className="sk-cube3 sk-cube" />
  </Container>
);

export default Loading;
