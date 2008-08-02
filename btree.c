#include "key.h"

/*!
  \file
  \brief Functions needed to build a BTREE index.
*/

#ifndef DOXYGEN_SHOULD_SKIP_THIS

  PG_FUNCTION_INFO_V1(spherekey_lt);
  PG_FUNCTION_INFO_V1(spherekey_le);
  PG_FUNCTION_INFO_V1(spherekey_eq);
  PG_FUNCTION_INFO_V1(spherekey_eq_neg);
  PG_FUNCTION_INFO_V1(spherekey_ge);
  PG_FUNCTION_INFO_V1(spherekey_gt);
  PG_FUNCTION_INFO_V1(spherekey_cmp);
  PG_FUNCTION_INFO_V1(spherepoint_cmp);
  PG_FUNCTION_INFO_V1(spherecircle_cmp);
  PG_FUNCTION_INFO_V1(sphereellipse_cmp);
  PG_FUNCTION_INFO_V1(sphereline_cmp);
  PG_FUNCTION_INFO_V1(spherepath_cmp);
  PG_FUNCTION_INFO_V1(spherepoly_cmp);
  PG_FUNCTION_INFO_V1(spherebox_cmp);

#endif



  /*!
    This function returns:
    - -2 if first key is less than second key
    - -1 if first key is less or equal than second key
    -  0 if keys are equal
    - +1 if first key is larger or equal than second key
    - +2 if first key is larger than second key
    \brief returns the relationship for two key values
    \param a first key
    \param b second key
    \return relationship
  */

  static int skey_cmp ( const int32 * a , const int32 * b )
  {

    static  const int32     dks =  ( MAXCVALUE + 1 ) / 2;
    static  int32     key[2][6] ;
    static  double         d[4] ;
    int32                  * hl = NULL ;
    static  double         fact ;
    static  int32          diff ;
    static  int            i, k ;
    static  int               h ;

    if ( memcmp ( (void*) a , (void*) b, KEYSIZE) == 0 ){
      return 0;
    }
    memcpy ( (void*) &key[0][0] , (void*) a , KEYSIZE );
    memcpy ( (void*) &key[1][0] , (void*) b , KEYSIZE );
    
    
    d[0] = d[1] = d[2] = d[3] = 0.0;
    diff  =   dks;
    fact  =   1.0;

    for ( i=0 ; i<(2*KEYSIZE); i++){

      for ( k=0; k<4; k++ ){

        switch (k) {
          case 0: hl = &key[0][0]; break; // a lower
          case 1: hl = &key[0][3]; break; // a upper
          case 2: hl = &key[1][0]; break; // b lower
          case 3: hl = &key[1][3]; break; // b upper
        }
        h = 0;
        if ( hl[0] < 0 ){
          hl[0] += diff;
        } else {
          h   |= 1;
          hl[0] -= diff;
        }
        if ( hl[1] < 0 ){
          hl[1] += diff;
        } else {
          h   |= 2;
          hl[1] -= diff;
        }
        if ( hl[2] < 0 ){
          hl[2] += diff;
        } else {
          h   |= 4;
          hl[2] -= diff;
        }
        d[k]  += ( h * fact );

      }

      if ( ( ( d[0] + fact ) < d[2] ) && ( ( d[1] + fact ) < d[2] ) ) return -2 ;
      if ( ( ( d[0] + fact ) < d[2] ) && ( ( d[1] + fact ) < d[3] ) ) return -1 ;
      if ( ( d[0] > ( d[3] + fact ) ) && ( d[1] > ( d[3] + fact ) ) ) return  2 ;
      if ( ( d[0] > ( d[2] + fact ) ) && ( d[1] > ( d[3] + fact ) ) ) return  1 ;
      if ( ( d[0] + fact ) < d[2] && d[1] > ( d[3] + fact ) )  return 0;
      if ( d[0] > ( d[2] + fact ) && ( d[1] + fact ) < d[3] )  return 0;

      fact /= 8.0 ;
      diff /=   2 ;

    }

    if ( ( d[0] < d[2] ) && ( d[1] < d[2] ) ) return -2 ;
    else
    if ( ( d[0] < d[2] ) && ( d[1] < d[3] ) ) return -1 ;
    else
    if ( ( d[0] > d[3] ) && ( d[1] > d[3] ) ) return  2 ;
    else
    if ( ( d[0] > d[2] ) && ( d[1] > d[3] ) ) return  1 ;

    return 0;
 
 
  }

  Datum  spherekey_lt(PG_FUNCTION_ARGS) {
    int32   * k1 =  ( int32 * )  PG_GETARG_POINTER ( 0 ) ;
    int32   * k2 =  ( int32 * )  PG_GETARG_POINTER ( 1 ) ;
    PG_RETURN_BOOL ( skey_cmp ( k1 , k2 ) == -2 );
  }

  Datum  spherekey_le(PG_FUNCTION_ARGS) {
    int32   * k1 =  ( int32 * )  PG_GETARG_POINTER ( 0 ) ;
    int32   * k2 =  ( int32 * )  PG_GETARG_POINTER ( 1 ) ;
    PG_RETURN_BOOL ( skey_cmp ( k1 , k2 ) == -1 );
  }

  Datum  spherekey_eq(PG_FUNCTION_ARGS) {
    int32   * k1 =  ( int32 * )  PG_GETARG_POINTER ( 0 ) ;
    int32   * k2 =  ( int32 * )  PG_GETARG_POINTER ( 1 ) ;
    PG_RETURN_BOOL ( skey_cmp ( k1 , k2 ) == 0 );
  }

  Datum  spherekey_eq_neg(PG_FUNCTION_ARGS) {
    int32   * k1 =  ( int32 * )  PG_GETARG_POINTER ( 0 ) ;
    int32   * k2 =  ( int32 * )  PG_GETARG_POINTER ( 1 ) ;
    PG_RETURN_BOOL (  skey_cmp ( k1 , k2 ) != 0 );
  }

  Datum  spherekey_ge(PG_FUNCTION_ARGS) {
    int32   * k1 =  ( int32 * )  PG_GETARG_POINTER ( 0 ) ;
    int32   * k2 =  ( int32 * )  PG_GETARG_POINTER ( 1 ) ;
    PG_RETURN_BOOL ( skey_cmp ( k1 , k2 ) == 1 );
  }

  Datum  spherekey_gt(PG_FUNCTION_ARGS) {
    int32   * k1 =  ( int32 * )  PG_GETARG_POINTER ( 0 ) ;
    int32   * k2 =  ( int32 * )  PG_GETARG_POINTER ( 1 ) ;
    PG_RETURN_BOOL ( skey_cmp ( k1 , k2 ) == 2 );
  }

  Datum  spherekey_cmp(PG_FUNCTION_ARGS) {
    int32   * k1 =  ( int32 * )  PG_GETARG_POINTER ( 0 ) ;
    int32   * k2 =  ( int32 * )  PG_GETARG_POINTER ( 1 ) ;
    PG_RETURN_INT32 ( skey_cmp ( k1 , k2 ) );
  }

  Datum  spherepoint_cmp(PG_FUNCTION_ARGS) {
    SPoint  * p1 =  ( SPoint * )  PG_GETARG_POINTER ( 0 ) ;
    SPoint  * p2 =  ( SPoint * )  PG_GETARG_POINTER ( 1 ) ;
    if ( spoint_eq ( p1,p2 ) ){
      PG_RETURN_INT32 ( 0 );
    } else { 
      static  int32 ak[6], bk[6] ;
      spherepoint_gen_key (  &ak[0] , p1 );
      spherepoint_gen_key (  &bk[0] , p2 );
      PG_RETURN_INT32 ( skey_cmp ( &ak[0] , &bk[0] ) );
    }
    PG_RETURN_INT32 ( 0 );
  }

  Datum  spherecircle_cmp(PG_FUNCTION_ARGS) {
    SCIRCLE  * c1 =  ( SCIRCLE * )  PG_GETARG_POINTER ( 0 ) ;
    SCIRCLE  * c2 =  ( SCIRCLE * )  PG_GETARG_POINTER ( 1 ) ;
    if ( scircle_eq ( c1,c2 ) ){
      PG_RETURN_INT32 ( 0 );
    } else { 
      static  int32 ak[6], bk[6] ;
      spherecircle_gen_key (  &ak[0] , c1 );
      spherecircle_gen_key (  &bk[0] , c2 );
      PG_RETURN_INT32 ( skey_cmp ( &ak[0] , &bk[0] ) );
    }
    PG_RETURN_INT32 ( 0 );
  }

  Datum  sphereellipse_cmp(PG_FUNCTION_ARGS) {
    SELLIPSE  * e1 =  ( SELLIPSE * )  PG_GETARG_POINTER ( 0 ) ;
    SELLIPSE  * e2 =  ( SELLIPSE * )  PG_GETARG_POINTER ( 1 ) ;
    if ( sellipse_eq ( e1,e2 ) ){
      PG_RETURN_INT32 ( 0 );
    } else { 
      static  int32 ak[6], bk[6] ;
      sphereellipse_gen_key (  &ak[0] , e1 );
      sphereellipse_gen_key (  &bk[0] , e2 );
      PG_RETURN_INT32 ( skey_cmp ( &ak[0] , &bk[0] ) );
    }
    PG_RETURN_INT32 ( 0 );
  }

  Datum  sphereline_cmp(PG_FUNCTION_ARGS) {
    SLine  * l1 =  ( SLine * )  PG_GETARG_POINTER ( 0 ) ;
    SLine  * l2 =  ( SLine * )  PG_GETARG_POINTER ( 1 ) ;
    if ( sline_eq ( l1,l2 ) ){
      PG_RETURN_INT32 ( 0 );
    } else { 
      static  int32 ak[6], bk[6] ;
      sphereline_gen_key (  &ak[0] , l1 );
      sphereline_gen_key (  &bk[0] , l2 );
      PG_RETURN_INT32 ( skey_cmp ( &ak[0] , &bk[0] ) );
    }
    PG_RETURN_INT32 ( 0 );
  }

  Datum  spherepath_cmp(PG_FUNCTION_ARGS) {
    SPATH  * p1 =  PG_GETARG_SPATH( 0 ) ;
    SPATH  * p2 =  PG_GETARG_SPATH( 1 ) ;
    if ( spath_eq ( p1,p2 ) ){
      PG_RETURN_INT32 ( 0 );
    } else { 
      static  int32 ak[6], bk[6] ;
      spherepath_gen_key (  &ak[0] , p1 );
      spherepath_gen_key (  &bk[0] , p2 );
      PG_RETURN_INT32 ( skey_cmp ( &ak[0] , &bk[0] ) );
    }
    PG_RETURN_INT32 ( 0 );
  }

  Datum  spherepoly_cmp(PG_FUNCTION_ARGS) {
    SPOLY  * p1 =  PG_GETARG_SPOLY( 0 ) ;
    SPOLY  * p2 =  PG_GETARG_SPOLY( 1 ) ;
    if ( spoly_eq ( p1,p2, FALSE ) ){
      PG_RETURN_INT32 ( 0 );
    } else { 
      static  int32 ak[6], bk[6] ;
      spherepoly_gen_key (  &ak[0] , p1 );
      spherepoly_gen_key (  &bk[0] , p2 );
      PG_RETURN_INT32 ( skey_cmp ( &ak[0] , &bk[0] ) );
    }
    PG_RETURN_INT32 ( 0 );
  }

  Datum  spherebox_cmp(PG_FUNCTION_ARGS) {
    SBOX  * b1 =  ( SBOX * )  PG_GETARG_POINTER ( 0 ) ;
    SBOX  * b2 =  ( SBOX * )  PG_GETARG_POINTER ( 1 ) ;
    if ( sbox_eq ( b1,b2 ) ){
      PG_RETURN_INT32 ( 0 );
    } else { 
      static  int32 ak[6], bk[6] ;
      spherebox_gen_key (  &ak[0] , b1 );
      spherebox_gen_key (  &bk[0] , b2 );
      PG_RETURN_INT32 ( skey_cmp ( &ak[0] , &bk[0] ) );
    }
    PG_RETURN_INT32 ( 0 );
  }


