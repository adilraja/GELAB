function stop = outfun(x,optimValues,state)
%This function is taken from Mathworks after discussions with them. https://uk.mathworks.com/help/optim/ug/output-functions.html
stop = false;

% Check if directional derivative is less than .01.
if(optimValues.directionalderivative < .01)
    stop = true;
end 

switch state
    case 'init'
        if(sum(isinf(optimValues.directionalderivative))>0 || sum(isnan(optimValues.directionalderivative))>0)
            stop=true;
        end
    case 'interrupt'
        stop=true;
    case 'iter'
           % Concatenate current point and objective function
           % value with history. x must be a row vector.
%            history.fval = [history.fval; optimValues.fval];
%            history.x = [history.x; x];
           % Concatenate current search direction with 
           % searchdir.
%            searchdir = [searchdir;...
%                         optimValues.searchdirection'];
%            plot(x(1),x(2),'o');
           % Label points with iteration number.
           % Add .15 to x(1) to separate label from plotted 'o'
%            text(x(1)+.15,x(2),num2str(optimValues.iteration));
    case 'done'
%            hold off
    otherwise
end
end