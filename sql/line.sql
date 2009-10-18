-- checking spherical line operators

SELECT sline ( spoint '(0, 90d)', spoint '(0, -89d)' )   =
       sline ( spoint '(0, 90d)', spoint '(0, -89d)' )  ;
SELECT sline ( spoint '(0,  90d)', spoint '(0, -89d)' )   <>
       sline ( spoint '(0, -89d)', spoint '(0,  90d)' ) ;



SELECT sline ( spoint '(0,   0d)', spoint '(10d, 0d)' )   #
       sline ( spoint '(5d,  5d)', spoint '(5d, -5d)' ) ;

SELECT sline ( spoint '(0,   0d)', spoint '(10d, 0d)' )   #
       sline ( spoint '(10d,  5d)', spoint '(10d, -5d)' ) ;

SELECT sline ( spoint '(0,   0d)', spoint '(10d, 0d)' )   #
       sline ( spoint '(15d,  5d)', spoint '(15d, -5d)' ) ;

SELECT sline ( spoint '(0,   0d)', spoint '(10d, 0d)' )   #
       sline ( spoint '(10d,  0d)', spoint '(10d, -5d)' ) ;



SELECT sline ( spoint '(0,   0d)', spoint '(10d, 0d)' )   #
       sline ( spoint '(5d,  -5d)', spoint '(5d, 5d)' ) ;

SELECT sline ( spoint '(0,   0d)', spoint '(10d, 0d)' )   #
       sline ( spoint '(10d, -5d)', spoint '(10d, 5d)' ) ;

SELECT sline ( spoint '(0,   0d)', spoint '(10d, 0d)' )   #
       sline ( spoint '(15d, -5d)', spoint '(15d, 5d)' ) ;

SELECT sline ( spoint '(0,   0d)', spoint '(10d, 0d)' )   #
       sline ( spoint '(10d,  0d)', spoint '(10d, 5d)' ) ;
       