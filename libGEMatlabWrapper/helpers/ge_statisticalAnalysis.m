function results=ge_statisticalAnalysis(stats, varargin)
 
[x, y]=size(stats.bestfithistory);

if(isempty(varargin))
%     figure;
%     grid on;
%     hold on;
%     for(i=1:y)
%         plot(stats.bestfithistory(1:x,i));
%     end
%     xlabel('Generations');
%     ylabel('Fitness (MSE_{s})');
    return;
end
results=[];

nargs=length(varargin);
for j=1:nargs
switch lower(varargin{j})
    case 'fh'
        [x, y]=size(stats.bestfithistory);
        mean_ =mean(stats.bestfithistory(x,:));
        std_ =std(stats.bestfithistory(x,:));
        min_ =min(stats.bestfithistory(x,:));
        max_ =max(stats.bestfithistory(x,:));
        results1=[mean_, std_, max_, min_];
        results=[results, results1];
        
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
        [x, y]=size(stats.testfithistory);
        mean_ =mean(stats.testfithistory(x,:));
        std_ =std(stats.testfithistory(x,:));
        min_ =min(stats.testfithistory(x,:));
        max_ =max(stats.testfithistory(x,:));
        results1=[mean_, std_, max_, min_];
        results=[results, results1];
    case 'rstrh'
        [x, y]=size(stats.bestrsquaretrainhistory);
        mean_ =mean(stats.bestrsquaretrainhistory(x,:));
        std_ =std(stats.bestrsquaretrainhistory(x,:));
        min_ =min(stats.bestrsquaretrainhistory(x,:));
        max_ =max(stats.bestrsquaretrainhistory(x,:));
        results1=[mean_, std_, max_, min_];
        results=[results, results1];
    case 'rsteh'
        [x, y]=size(stats.bestrsquaretesthistory);
        mean_ =mean(stats.bestrsquaretesthistory(x,:));
        std_ =std(stats.bestrsquaretesthistory(x,:));
        min_ =min(stats.bestrsquaretesthistory(x,:));
        max_ =max(stats.bestrsquaretesthistory(x,:));
        results1=[mean_, std_, max_, min_];
        results=[results, results1];
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