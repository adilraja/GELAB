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

function [c_ind1, c_ind2] = ge_nocrossover (ind1, ind2, params)

genome1=ind1.genome(:);
genome2=ind2.genome(:);


%Crossover scheme for variable length genome.
  c_ind1=ind1;
  c_ind2=ind2;

  

c_ind1.operator=1;
c_ind2.operator=1;

end
