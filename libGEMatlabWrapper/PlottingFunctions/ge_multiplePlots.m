function ge_multiplePlots(c_stats, varargin)
%Call ge_plots in a loop to create many plots of the same type. Muhammad
%Adil Raja. 27th February, 2019.


length_stats=length(c_stats);
for(i=1:length_stats)
    ge_plots(c_stats(i), varargin{:});
end