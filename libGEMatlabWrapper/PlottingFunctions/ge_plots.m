function ge_plots(stats)
 
[x, y]=size(stats.bestfithistory);

for(i=1:y)
%    figure;
   plot(stats.bestfithistory(1:x,i));
   grid on;
   hold on;
   xlabel('Generations');
   ylabel('Fitness (MSE_{s})');
%    title('Best Fitness History');
%    figure;
%    plot(stats.meanfithistory(:,i));
%    figure;
%    plot(stats.testfithistory(:,i));
%    figure;
%    plot(stats.diversityhistory(:,i));
%    figure;
%    plot(stats.numvalidhistory(:,10));
end
end