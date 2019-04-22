program matrixMultiplication
implicit none
integer, parameter :: n = 3 ! Parameter N defining size of matrices
real(kind=8),allocatable::matriz(:,:),vetor(:),resultado1(:),resultado2(:)  ! Defining 3 matrices that will be allocatated in memory during executions
integer(kind=4) :: i, j ! Iterators
real :: start,finish ! Variables to make timing
real(kind=8) :: r1,r2 

allocate(matriz(n,n),vetor(n),resultado1(n),resultado2(n)) ! Alocating the matrices based on parameter n

! Filling up values to matrix 
do i = 1, n
 do j = 1, n    
    call random_number(r1)
    r1 = r1 * 100
    matriz(i, j) =  r1
  end do
end do

! Filling up values to vector 
do i = 1, n
    call random_number(r2)
    r2 = r2 * 100
    vetor(i) = r2
end do

!Tipo 1 de Multiplicacao
do j = 1, n
    do i = 1, n
        resultado1(j) = resultado1(j) + matriz(j,i) * vetor(i) 
    end do 
end do

!Tipo 2 de Multiplicacao
do i = 1, n
    do j = 1,n
        resultado2(i) = resultado2(i) + matriz(j,i) * vetor(j)
    end do
end do

do i = 1, n
    do j = 1, n
        print *, matriz(i,j)
    end do
end do
print *,"Essa foi a matriz"

do i = 1, n
        print *, vetor(i)
end do

print *,"Essa foi o vetor"

do i = 1, n
        print *, resultado1(i)
end do

print *,"Essa foi o resultado1"

do i = 1, n
        print *, resultado2(i)
end do

print *,"Essa foi o resultado2"

end program matrixMultiplication