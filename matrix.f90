program matrixVectorMultiplication

implicit none
integer, parameter :: n = 13000 ! Variavel que define o tamanho das matrizes
real(kind=8),allocatable::matriz(:,:),vetor(:),resultado1(:),resultado2(:)  ! Definicao das 4 matrizes usadas no programa
integer(kind=4) :: i, j ! Iteradores
real :: start,finish ! Contagem de tempo
real(kind=8) :: r1,r2 ! Numeros aleatorios
integer :: tid, omp_get_thread_num  

allocate(matriz(n,n),vetor(n),resultado1(n),resultado2(n)) ! Alocacao das matrizes

! Inicializando a matriz A com numeros aleatorios (Ax = B)
do i = 1, n
 do j = 1, n
    call random_number(r1)
    r1 = r1 * 100
    matriz(i, j) =  r1
  end do
end do

! Inicializando o vetor x com numeros aleatorios (Ax = B)
call cpu_time(start)
!$ call omp_set_num_threads(2)
!$omp parallel do schedule(static) &
!$omp shared(vetor) &
!$omp private(i, r2, tid)
do i = 1, n
    tid = omp_get_thread_num()
    PRINT *, 'Hello World from thread = ', TID
    call random_number(r2)
    r2 = r2 * 100
    vetor(i) = r2
end do
!$omp end parallel do
call cpu_time(finish)
print '("Tempo (criacao do vetor) = ",f6.3," segundos.")',finish-start

! Tipo 1 de Multiplicacao (por linhas)
call cpu_time(start)
do j = 1, n
    do i = 1, n
        resultado1(j) = resultado1(j) + matriz(j, i) * vetor(i)
    end do
end do
call cpu_time(finish)
print '("Tempo (multiplicacao por linhas) = ",f6.3," segundos.")',finish-start

! Tipo 2 de Multiplicacao (por colunas)
call cpu_time(start)
do i = 1, n
    do j = 1,n
        resultado2(j) = resultado2(j) + matriz(j,i) * vetor(i)
    end do
end do
call cpu_time(finish)
print '("Tempo (multiplicacao por colunas) = ",f6.3," segundos.")',finish-start

end program matrixVectorMultiplication
