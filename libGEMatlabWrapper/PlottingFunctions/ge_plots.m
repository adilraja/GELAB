function ge_plots(stats, varargin)
 
% [x, y]=size(stats(1).bestfithistory);

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

nargs=length(varargin);
for j=1:nargs
switch lower(varargin{j})
    case 'boxpf'
        stats_l=length(stats);
        fitness=[];
        testfitness=[];
        [x, y]=size(stats(1).bestfithistory);
        for(ii=1:stats_l)
            fitness(:,ii)=stats(ii).bestfithistory(x, :);
            testfitness(:,ii)=stats(ii).testfithistory(x, :);
        end
        size(fitness);
        boxplot(fitness);
        grid on;
        xlabel('Experiment NUmber');
        ylabel('Fitness (MSE)');
    case 'boxptf'
        stats_l=length(stats);
        fitness=[];
        testfitness=[];
        [x, y]=size(stats(1).bestfithistory);
        for(ii=1:stats_l)
            testfitness(:,ii)=stats(ii).testfithistory(x, :);
        end
        size(testfitness);
        boxplot(testfitness);
        grid on;
        xlabel('Experiment NUmber');
        ylabel('Fitness (MSE)');
    case 'scoreherr'
        [x,y]=size(stats);
        mylinespec=['b:', 'rx--', 'g-.', 'c+:', 'm-.-'];
        for(i=1:y)
            figure;
            grid on;
            hold on;
            for(j=1:x)
                score_f=1./(1+stats{j, i}.bestfithistory);
                mean_f=mean(score_f,2);
                err_f=1.96*std(score_f, 0, 2)/sqrt(size(score_f,2));
                errorbar(mean_f, err_f, mylinespec(j), 'LineWidth',1.5);
            end
            xlabel('Generations');
            ylabel('Score');
            legend('SA', 'GA', 'PSO', 'GE', 'GP');
        end
    case 'tscoreherr'
        [x,y]=size(stats);
        mylinespec=['b:', 'rx--', 'g-.', 'c+:', 'm-.-'];
        for(i=1:y)
            figure;
            grid on;
            hold on;
            for(j=1:x)
                score_f=1./(1+stats{j, i}.testfithistory);
                mean_f=mean(score_f,2);
                err_f=1.96*std(score_f, 0, 2)/sqrt(size(score_f,2)); 
                errorbar(mean_f, err_f, mylinespec(j), 'LineWidth',1.5);
            end
            xlabel('Generations');
            ylabel('Score');
            legend('SA', 'GA', 'PSO', 'GE', 'GP');
        end
    case 'cumtimeherr'
        [x,y]=size(stats);
        mylinespec=['b:', 'rx--', 'g-.', 'c+:', 'm-.-'];
        for(i=1:y)
            figure;
            grid on;
            hold on;
            for(j=1:x)
                score_f=cumsum(stats{j, i}.timehistory)./60;
                mean_f=mean(score_f,2);
                err_f=1.96*std(score_f, 0, 2)/sqrt(size(score_f,2));
                errorbar(mean_f, err_f, mylinespec(j), 'LineWidth',1.5);
            end
            xlabel('Generations');
            ylabel('Time (Minutes)');
            legend('SA', 'GA', 'PSO', 'GE', 'GP');
        end
    case 'timeherr'
        [x,y]=size(stats);
        mylinespec=['b:', 'rx--', 'g-.', 'c+:', 'm-.-'];
        for(i=1:y)
            figure;
            grid on;
            hold on;
            for(j=1:x)
                score_f=stats{j, i}.timehistory;
                mean_f=mean(score_f,2);
                err_f=1.96*std(score_f, 0, 2)/sqrt(size(score_f,2));
                errorbar(mean_f, err_f, mylinespec(j), 'LineWidth',1.5);
            end
            xlabel('Generations');
            ylabel('Time (Seconds)');
            legend('SA', 'GA', 'PSO', 'GE', 'GP');
        end
    case 'fherr'
        mean_f=mean(stats{1,1}.bestfithistory,2);
        err_f=std(stats{1,1}.bestfithistory, 0, 2);
        figure;
        grid on;
        hold on;
        errorbar(mean_f, err_f, 'r-.');
        xlabel('Generations');
        ylabel('Fitness (MSE)');
    case 'fh'
        figure;
        grid on;
        hold on;
        for(i=1:y)
            plot(stats.bestfithistory(1:x,i));
        end
        xlabel('Generations');
        ylabel('Fitness (MSE)');
    case 'mfh'
        figure;
        grid on;
        hold on;
        for(i=1:y)
            plot(stats.meanfithistory(:,i));
        end
        xlabel('Generations');
        ylabel('Fitness (MSE)');
    case 'tfherr'
        mean_f=mean(stats.testfithistory,2);
        err_f=std(stats.testfithistory, 0, 2);
        figure;
        grid on;
        hold on;
        errorbar(mean_f, err_f);
%         for(i=1:y)
%             plot(stats.bestfithistory(1:x,i));
%         end
        xlabel('Generations');
        ylabel('Fitness (MSE)');
    case 'tfh'
        figure;
        grid on;
        hold on;
        for(i=1:y)
            plot(stats.testfithistory(:,i));    
        end
        xlabel('Generations');
        ylabel('Fitness (MSE)');
    case 'rstrh'
        figure;
        grid on;
        hold on;
        for(i=1:y)
            plot(stats.bestrsquaretrainhistory(:,i));    
        end
        xlabel('Generations');
        ylabel('R^{2}');
    case 'rsteh'
        figure;
        grid on;
        hold on;
        for(i=1:y)
            plot(stats.bestrsquaretesthistory(:,i));    
        end
        xlabel('Generations');
        ylabel('R^{2}');
    case 'dh'
        mean_f=mean(stats.diversityhistory, 2);
        err_f=1.96*std(stats.diversityhistory, 0, 2)./sqrt(size(stats.diversityhistory, 2));
        figure;
        grid on;
        hold on;
        errorbar(mean_f, err_f);
        xlabel('Generations');
        ylabel('Diversity');
    case 'dissh'
        mean_f=mean(stats.disimilarityhistory,2);
        err_f=1.96*std(stats.dissimilarityhistory, 0, 2)./sqrt(size(stats.dissimilarityhistory, 2));
        figure;
        grid on;
        hold on;
        errorbar(mean_f, err_f);
        xlabel('Generations');
        ylabel('Dissimilarity Index');
    case 'divhisterr'
        [x,y]=size(stats);
        mylinespec=['b:', 'rx--', 'g-.', 'c+:', 'm-.-'];
        for(i=1:y)
            figure;
            grid on;
            hold on;
            for(j=1:x)
                score_f=stats{j, i}.diversityhistory;
                mean_f=mean(score_f,2);
                err_f=1.96*std(score_f, 0, 2)/sqrt(size(score_f,2)); 
                errorbar(mean_f, err_f, mylinespec(j), 'LineWidth',1.5);
            end
            xlabel('Generations');
            ylabel('Diversity');
            legend('SA', 'GA', 'PSO', 'GE', 'GP');
        end
    case 'dissimhisterr'
        [x,y]=size(stats);
        mylinespec=['b:', 'rx--', 'g-.', 'c+:', 'm-.-'];
        for(i=1:y)
            figure;
            grid on;
            hold on;
            for(j=1:x)
                score_f=stats{j, i}.dissimilarityhistory;
                mean_f=mean(score_f,2);
                err_f=1.96*std(score_f, 0, 2)/sqrt(size(score_f,2)); 
                errorbar(mean_f, err_f, mylinespec(j), 'LineWidth',1.5);
            end
            xlabel('Generations');
            ylabel('Dissimilarity Index');
            legend('SA', 'GA', 'PSO', 'GE', 'GP');
        end
    case 'nvhisterr'
        [x,y]=size(stats);
        mylinespec=['b:', 'rx--', 'g-.', 'c+:', 'm-.-'];
        for(i=1:y)
            figure;
            grid on;
            hold on;
            for(j=1:x)
                score_f=stats{j, i}.numvalidhistory;
                mean_f=mean(score_f,2);
                err_f=1.96*std(score_f, 0, 2)/sqrt(size(score_f,2)); 
                errorbar(mean_f, err_f, mylinespec(j), 'LineWidth',1.5);
            end
            xlabel('Generations');
            ylabel('Num. Valid');
            legend('SA', 'GA', 'PSO', 'GE', 'GP');
        end
    case 'therr'
        mean_f=mean(stats.timehistory,2);
        err_f=std(stats.timehistory, 0, 2);
        figure;
        grid on;
        hold on;
        errorbar(mean_f, err_f);
        xlabel('Generations');
        ylabel('Time (Seconds)');
    case 'th'
        figure;
        grid on;
        hold on;
        for(i=1:y)
            plot(stats.timehistory(:,i));   
        end
        xlabel('Generations');
        ylabel('Time (Seconds)');
    case 'cumth'
        cumt=cumsum(stats.timehistory);
        mean_f=mean(cumt,2);
        err_f=std(cumt, 0, 2);
        figure;
        grid on;
        hold on;
        errorbar(mean_f, err_f);
        xlabel('Generations');
        ylabel('Time (Seconds)');
    case 'nvherr'
        mean_f=mean(stats.numvalidhistory,2);
        err_f=std(stats.numvalidhistory, 0, 2);
        figure;
        grid on;
        hold on;
        errorbar(mean_f, err_f);
        xlabel('Generations');
        ylabel('Num. Valid');
    case 'nvh'
        figure;
        grid on;
        hold on;
        for(i=1:y)
            plot(stats.numvalidhistory(:,i));   
        end
        xlabel('Generations');
        ylabel('Num. Valid');
    case 'spxoverherr'
        mean_f=mean(stats.spxoverhistory,2);
        err_f=std(stats.spxoverhistory, 0, 2);
        figure;
        grid on;
        hold on;
        errorbar(mean_f, err_f);
        xlabel('Generations');
        ylabel('Probability');
    case 'vpxoverh'
        mean_f=mean(stats.vpxoverhistory,2);
        err_f=std(stats.vpxoverhistory, 0, 2);
        figure;
        grid on;
        hold on;
        errorbar(mean_f, err_f);
        xlabel('Generations');
        ylabel('Probability');
    case 'subtreexoverh'
        mean_f=mean(stats.subtreexoverhistory,2);
        err_f=std(stats.subtreexoverhistory, 0, 2);
        figure;
        grid on;
        hold on;
        errorbar(mean_f, err_f);
        xlabel('Generations');
        ylabel('Probability');
    case 'wh'
        mean_f=mean(stats.weavehistory,2);
        err_f=std(stats.weavehistory, 0, 2);
        figure;
        grid on;
        hold on;
        errorbar(mean_f, err_f);
        xlabel('Generations');
        ylabel('Probability');
    case 'twh'
        mean_f=mean(stats.tweavehistory,2);
        err_f=std(stats.tweavehistory, 0, 2);
        figure;
        grid on;
        hold on;
        errorbar(mean_f, err_f);
        xlabel('Generations');
        ylabel('Probability');
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
        mean_f=mean(stats.pmutationhistory,2);
        err_f=std(stats.pmutationhistory, 0, 2);
        figure;
        grid on;
        hold on;
        errorbar(mean_f, err_f);
        xlabel('Generations');
        ylabel('Probability');
    case 'fpmh'
        mean_f=mean(stats.fpmutationhistory,2);
        err_f=std(stats.fpmutationhistory, 0, 2);
        figure;
        grid on;
        hold on;
        errorbar(mean_f, err_f);
        xlabel('Generations');
        ylabel('Probability');
    case 'fbmh'
        mean_f=mean(stats.fbmutationhistory,2);
        err_f=std(stats.fbmutationhistory, 0, 2);
        figure;
        grid on;
        hold on;
        errorbar(mean_f, err_f);
        xlabel('Generations');
        ylabel('Probability');
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