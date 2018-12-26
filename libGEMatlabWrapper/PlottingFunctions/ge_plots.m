function ge_plots(stats, varargin)
 
[x, y]=size(stats.bestfithistory);

if(isempty(varargin))
    figure;
    grid on;
    hold on;
    for(i=1:y)
        plot(stats.bestfithistory(1:x,i));
    end
    xlabel('Generations');
    ylabel('Fitness (MSE_{s})');
    return;
end

nargs=length(varargin);
for j=1:nargs
switch lower(varargin{j})
    case 'fh'
        figure;
        grid on;
        hold on;
        for(i=1:y)
            plot(stats.bestfithistory(1:x,i));
        end
        xlabel('Generations');
        ylabel('Fitness (MSE_{s})');
    case 'mfh'
        figure;
        grid on;
        hold on;
        for(i=1:y)
            plot(stats.meanfithistory(:,i));
        end
        xlabel('Generations');
        ylabel('Fitness (MSE_{s})');
    case 'tfh'
        figure;
        grid on;
        hold on;
        for(i=1:y)
            plot(stats.testfithistory(:,i));    
        end
        xlabel('Generations');
        ylabel('Fitness (MSE_{s})');
    case 'dh'
        figure;
        grid on;
        hold on;
        for(i=1:y)
            plot(stats.diversityhistory(:,i));   
        end
        xlabel('Generations');
        ylabel('Diversity');
    case 'nvh'
        figure;
        grid on;
        hold on;
        for(i=1:y)
            plot(stats.numvalidhistory(:,i));   
        end
        xlabel('Generations');
        ylabel('Num. Valid');
    case 'spxoverh'
        figure;
        grid on;
        hold on;
        for(i=1:y)
            plot(stats.spxoverhistory(:,i));   
        end
        xlabel('Generations');
        ylabel('Crossover Probability');
    case 'vpxoverh'
        figure;
        grid on;
        hold on;
        for(i=1:y)
            plot(stats.vpxoverhistory(:,i));   
        end
        xlabel('Generations');
        ylabel('Crossover Probability');
    case 'wh'
        figure;
        grid on;
        hold on;
        for(i=1:y)
            plot(stats.weavehistory(:,i));   
        end
        xlabel('Generations');
        ylabel('Weave Probability');
    case 'twh'
        figure;
        grid on;
        hold on;
        for(i=1:y)
            plot(stats.tweavehistory(:,i));   
        end
        xlabel('Generations');
        ylabel('Weave Probability');
    case 'xoverh'
        figure;
        grid on;
        hold on;
        plot(stats.spxoverhistory(:,1));
        plot(stats.vpxoverhistory(:,1)); 
        plot(stats.weavehistory(:,1));
        plot(stats.tweavehistory(:,1));
        xlabel('Generations');
        ylabel('Xover Probability');
        legend('SPXover', 'VPXover', 'Weave', 'TWeave');
    case 'pmh'
        figure;
        grid on;
        hold on;
        for(i=1:y)
            plot(stats.pmutationhistory(:,i));   
        end
        xlabel('Generations');
        ylabel('Point Mutation Probability');
    case 'fpmh'
        figure;
        grid on;
        hold on;
        for(i=1:y)
            plot(stats.fpmutationhistory(:,i));   
        end
        xlabel('Generations');
        ylabel('Few Points Mutation Probability');
    case 'fbmh'
        figure;
        grid on;
        hold on;
        for(i=1:y)
            plot(stats.fbmutationhistory(:,i));   
        end
        xlabel('Generations');
        ylabel('Fixed Bounds Mutation Probability');
    case 'mutationh'
        figure;
        grid on;
        hold on;
        plot(stats.pmutationhistory(:,1));
        plot(stats.fpmutationhistory(:,1));
        plot(stats.fbmutationhistory(:,1));
        xlabel('Generations');
        ylabel('Mutation Probability');
        legend('Point', 'Few points', 'All Points');
    otherwise
          error(['Unexpected option: ' varargin{j}])
    end
%   j=j+2;
end

end