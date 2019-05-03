dnl @synopsis C_FLAGS_CHECK [compiler flags]                                        
dnl @summary check whether compiler supports given C flags or not                   
AC_DEFUN([C_FLAG_CHECK],                                                            
[dnl                                                                                  
  AC_MSG_CHECKING([if $CC supports $1])
  AC_LANG_PUSH([C])
  ac_saved_cflags="$CFLAGS"                                                       
  CFLAGS="-Werror $1"                                                               
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([])],                                            
    [AC_MSG_RESULT([yes])],                                                           
    [AC_MSG_ERROR([no])]                                                              
  )                                                                                   
  CFLAGS="$ac_saved_cflags"                                                       
  AC_LANG_POP([C])
])
