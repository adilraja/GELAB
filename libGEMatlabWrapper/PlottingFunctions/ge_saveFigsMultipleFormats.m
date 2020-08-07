function ge_saveFigsMultipleFormats(filename, varargin)
%function saveFigsMultipleFormats(cf, filename)
%This file saves a figure in multiple formats. You have to supply a figure
%handle (a number such as 1, 2, 3) as an input and the target file name.
%The routine will save the file in .fig, .pdf, .eps and .jpg formats. This
%is useful for research when you require the same plot or figure in
%multiple formats. Written by Muhammad Adil Raja, 8th July, 2018.

pdffig=strcat(filename, '.pdf');
jpgfig=strcat(filename, '.jpg');
epsfig=strcat(filename, '.eps');
figfig=strcat(filename, '.fig');
directory='Figs';

nargs=length(varargin);
for j=1:2:nargs
    cf=varargin{j};
    prefix=varargin{j+1};
    
    saveas(cf, strcat(directory, '/pdf/', prefix, '-', pdffig));
    saveas(cf, strcat(directory, '/jpg/', prefix, '-', jpgfig));
    saveas(cf, strcat(directory, '/eps/', prefix, '-', epsfig), 'epsc');
    saveas(cf, strcat(directory, '/fig/', prefix, '-', figfig));
end


