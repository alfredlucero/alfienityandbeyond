echo on

n = 4

Perm = perms(n:-1:1)    % Perm is a  24 x 4  table of all permutations of size 4

pause

Ident = eye(n)

P = zeros(n,n,n)
for i = 1:n
   P(:,:,i) = Ident( :, Perm(i,:) )
   %  P(:,:,i) is the i-th permutation matrix:
   %    the Identity matrix with columns permuted into Perm(i)
end

Perm(1:3, :)   % the first 3 permutations

P1 = P(:,:,1)  % the identity permutation
P2 = P(:,:,2)  % the permutation that interchanges 3 and 4
P3 = P(:,:,3)  % the permutation that interchanges 2 and 3

pause

x = (1:4)'


P1 * x

P2 * x

P3 * x


pause

P2 * P3

P2 * P3 * x


P3 * P2

P3 * P2 * x

echo off
