import { styled } from 'goober';
import { FunctionalComponent, h } from 'preact';

const StyledButton = styled('button')`
  position: relative;
  overflow: hidden;
  transition: background 400ms;
  color: #fff;
  background-color: #6200ee;
  padding: 1rem 2rem;
  font-family: 'Roboto', sans-serif;
  font-size: 1.5rem;
  outline: 0;
  border: 0;
  border-radius: 0.25rem;
  box-shadow: 0 0 0.5rem rgba(0, 0, 0, 0.3); /* black with 30% opacity */
  cursor: pointer;

  &:disabled {
    background-color: gray;
  }

  span.ripple {
    position: absolute;
    border-radius: 50%;
    transform: scale(0);
    animation: ripple 600ms linear;
    background-color: rgba(255, 255, 255, 0.7);
  }

  @keyframes ripple {
    to {
      transform: scale(4);
      opacity: 0;
    }
  }
`;

const Button: FunctionalComponent<any> = ({ onClick, ...props }) => {
  function createRipple(event: any) {
    console.log(event);
    const button = event.currentTarget;
    const circle = document.createElement('span');

    circle.style.width = `${button.clientWidth}px`;
    circle.style.height = `${button.clientWidth}px`;

    circle.style.right = '0px';
    circle.style.top = '0px';
    circle.style.bottom = '0px';
    circle.style.left = '0px';

    circle.style.margin = 'auto';

    circle.classList.add('ripple');

    const ripple = button.getElementsByClassName('ripple')[0];

    if (ripple) {
      ripple.remove();
    }

    button.appendChild(circle);
    if (onClick) onClick();
  }

  return (
    <StyledButton {...props} onClick={createRipple}>
      {props.children}
    </StyledButton>
  );
};

export default Button;
