% ## Copyright (C) 2017 FGFS
% ## 
% ## This program is free software; you can redistribute it and/or modify it
% ## under the terms of the GNU General Public License as published by
% ## the Free Software Foundation; either version 3 of the License, or
% ## (at your option) any later version.
% ## 
% ## This program is distributed in the hope that it will be useful,
% ## but WITHOUT ANY WARRANTY; without even the implied warranty of
% ## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
% ## GNU General Public License for more details.
% ## 
% ## You should have received a copy of the GNU General Public License
% ## along with this program.  If not, see <http://www.gnu.org/licenses/>.
% 
% ## -*- texinfo -*- 
% ## @deftypefn {Function File} {@var{retval} =} Crossover (@var{input1}, @var{input2})
% ##
% ## @seealso{}
% ## @end deftypefn
% 
% ## Author: FGFS <fgfs@fgfs-Precision-WorkStation-T3500>
% ## Created: 2017-03-16

function [c_ind1, c_ind2] = ge_rossover (ind1, ind2)

genome1=ind1.genome;
genome2=ind2.genome;
[x, y]=size(genome1);

if(rand(1)<0.5)%perform column-wise crossover
  y2=floor(rand(1)*(y-1))+1;
  y2=y/2;

 % c_genome1=zeros(x, y);
  c_genome1(:, 1:y2)= genome1(:, 1:y2);
  c_genome1(:,y2+1:y)=genome2(:,y2+1:y);
  flip_prob=rand(1);
  if(flip_prob<0.3)
    c_genome1=flip(c_genome1, 2);
  elseif(flip_prob>0.3 && flip_prob<0.6)
    c_genome1=flip(c_genome1);
  endif

%  c_genome2=zeros(x, y);
  c_genome2(:, 1:y2)= genome2(:, 1:y2);
  c_genome2(:,y2+1:y)=genome1(:,y2+1:y);
  flip_prob=rand(1);
  if(flip_prob<0.3)
    c_genome2=flip(c_genome2, 2);
  elseif(flip_prob>0.3 && flip_prob<0.6)
    c_genome2=flip(c_genome2);
  endif


  c_ind1=createIndividual;
  c_ind2=createIndividual;

  c_ind1.genome=c_genome1;
  c_ind2.genome=c_genome2;
else%perform row-wise crossover
  x2=floor(rand(1)*(x-1))+1;

%  c_genome1=zeros(x, y);
  c_genome1(1:x2, :)= genome1(1:x2, :);
  c_genome1(x2+1:x, :)=genome2(x2+1:x, :);

 % c_genome2=zeros(x, y);
  c_genome2(1:x2, :)= genome2(1:x2, :);
  c_genome2(x2+1:x, :)=genome1(x2+1:x, :);

  c_ind1=createIndividual;
  c_ind2=createIndividual;

  c_ind1.genome=c_genome1;
  c_ind2.genome=c_genome2;
end
c_ind1.left_parent=ind1.ID;
c_ind1.right_parent=ind2.ID;

c_ind2.left_parent=ind2.ID;
c_ind2.right_parent=ind1.ID;

end
