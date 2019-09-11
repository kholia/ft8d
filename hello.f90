! $ gfortran hello.f90; ./a.out backup/ft8_14074000.c2
!  20
! 14074000

program hello

  include 'ft8_params.f90'
  character infile*80
  character df*8
  real*8 dialfreq

  nargs=iargc()
  if(nargs.ne.1) then
    print*,'Usage: ft8d file'
    go to 999
  endif

  call getarg(1,infile)
  open(10,file=infile,status='old',access='stream')
  read(10,end=999) dd
  ! read(10,end=999) dialfreq,dd
  close(10)
  j2=index(infile,'.c2')
  write(*,1) j2
1 format(i4)

  df=infile(j2-8:j2)
  read(df ,*) dialfreq
  ! dialfreq = 14074000.0 ! temporary hack
  write(*,2) nint(dialfreq)
2 format(i9)

999 end program hello
