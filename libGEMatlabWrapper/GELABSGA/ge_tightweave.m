%function [c_ind1, c_ind2] = ge_weave (ind1, ind2, params). This function
%performs simple linear operations of addition and subtration on two
%genotype arrays to create two new individuals. Written by Muhammad Adil
%Raja, November, 04, 2018.
function [c_ind1, c_ind2] = ge_tightweave (ind1, ind2, params)

genome_length=params.genome_length;
grammar=params.grammar;

genome1=ind1.genome;
genome2=ind2.genome;
genome1=ind1.genome(:);
genome2=ind2.genome(:);
gl1=length(genome1);
gl2=length(genome2);

if(gl1<gl2)
    cg1=[genome1; zeros(gl2-gl1,1)];
    cg2=genome2;
    cgl1=gl2;
    cgl2=gl2;
elseif(gl2<gl1)
    cg1=genome1;
    cg2=[genome2; zeros(gl1-gl2,1)];
    cgl1=gl1;
    cgl2=gl1;
else
    cg1=genome1;
    cg2=genome2;
    cgl1=gl1;
    cgl2=gl1;
end
twv1=int32(randi([0, 1],cgl1,1)*2-1);
twv2=int32(randi([0, 1],cgl1,1)*2-1);
  c_genome1= abs(cg1+(cg2.*twv1));

  c_genome2= abs(cg1+(cg2.*twv2));

  c_ind1=ge_createIndividual(params, 0);
  c_ind2=ge_createIndividual(params, 0);

  c_ind1.genome=c_genome1;
  c_ind2.genome=c_genome2;
  
%   c_ind1.grammar.setGenotype(c_ind1.genome, length(c_ind1.genome));
%   c_ind2.grammar.setGenotype(c_ind2.genome, length(c_ind2.genome));
c_ind1.left_parent=ind1.ID;
c_ind1.right_parent=ind2.ID;

c_ind1.constants=ind1.constants;
c_ind2.constants=ind2.constants;

c_ind2.left_parent=ind2.ID;
c_ind2.right_parent=ind1.ID;

c_ind1.operator=4;
c_ind2.operator=4;

end
