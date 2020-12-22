%% Quick and dirty MATLAB code to convert a Matlab Matrix
%% to a simple LaTex table
%% For the World
%% Amit Saha (http://amitksaha.wordpress.com)

function tablatex(matrix, filename)
    
    fid = fopen(filename,'w');
    
    
    %fprintf(fid,'\\documentclass{article}\n');
    %fprintf(fid,'\\begin{document}\n');
    fprintf(fid,' \\begin{tabular}{ |');
    
    for col=1:(size(matrix,2)+2)
        fprintf(fid,'c | ');
    end
    fprintf(fid,'}\n\\hline\n');
    size(matrix)
    % now write the elements of the matrix
    for r=1:size(matrix,1)
        for c=1:size(matrix,2)
            A_str = sprintf('%.2e',matrix(r,c));
            A_str = strrep(A_str, 'e+0','e+');
            A_str = strrep(A_str, 'e-0','e-');
            if c==size(matrix,2)
                fprintf(fid,'%s',A_str);
            elseif c==1
                fprintf(fid,'& & %s & ',A_str);
            else
                fprintf(fid,'%s & ',A_str);
            end
            A_str=[];
        end            
        
        fprintf(fid,' \\\\ \\hline \n');
    end
    
    
    fprintf(fid,'\\hline\n');
    fprintf(fid,'\\end{tabular}\n');
    fprintf(fid,'\\end{document}\n');
    fclose(fid);
    
    
    return
    