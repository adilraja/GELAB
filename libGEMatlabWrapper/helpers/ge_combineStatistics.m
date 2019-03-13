function c_stats=ge_combineStatistics(c_stats, stats)

%Combines statistics of multiple experiments. Muhammad Adil Raja. 27 Feb,
%2019. function c_stats=ge_combineStatistics(c_stats, stats)

if(nargin==1)
    return;
end

c_stats=[c_stats; stats];