%function params=ge_updateparams(varargin) takes in a variable number of
%arguments and sets the parameters according to that. Written by Muhammad
%Adil Raja, 15th November, 2018
function params=ge_updateparams(params, varargin)

j=1;
if(isempty(varargin))
    return;
end
nargs=length(varargin);
for j=1:2:nargs
switch lower(varargin{j})
    case 'selection'
      params.selectionFunction = varargin{j+1};
    case 'mutationp'
      params.mutationProbability = varargin{j+1};
    case 'spxoverp'
        params.spxoverProb=varagrin{j+1};
    case 'vpxoverp'
        params.vpxoverProb=varargin{j+1};
    case 'weavep'
        params.weaveProb=varargin{j+1};
    case 'tweavep'
        params.tweaveProb=varargin{j+1};
    otherwise
          error(['Unexpected option: ' varargin{j}])
    end
%   j=j+2;
end