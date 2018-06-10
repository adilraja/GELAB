% ## Copyright (C) 2016 Adil
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
% ## @deftypefn {Function File} {@var{retval} =} acceptance_probability_for_simulated_annealing (@var{input1}, @var{input2})
% ##Computes acceptance probability for simulated annealing. I got inspiration for this from http://katrinaeg.com/simulated-annealing.html
% ## @seealso{}
% ## @end deftypefn
% 
% ## Author: Adil <adil@adil-HP-250-G3-Notebook-PC>
% ## Created: 2016-08-14

function [retval] = ge_accept_prob_sa (old_cost, new_cost, T)
%Inspiration for this comes from http://katrinaeg.com/simulated-annealing.html
if(new_cost<old_cost)
  retval=1.0;
elseif(isnan(new_cost) || isinf(new_cost))
  retval=0;
else
  retval=exp((old_cost-new_cost)/T);
end
end
