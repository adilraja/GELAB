function statis=ge_statistics()
%Returns a stats struct to hold various statistics about GE runs. Muhammad
%Adil Raja. 20th June, 2018
statis=struct('bestfithistory', [], 'meanfithistory', [], 'testfithistory', [], 'timehistory', [], 'numvalidhistory', [], 'diversityhistory', [], 'dissimilarityhistory', [], 'bestrsquaretrainhistory', [], 'bestrsquaretesthistory', []);