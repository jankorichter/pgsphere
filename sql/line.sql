-- checking spherical line operators

SELECT sline ( spoint '(0, 90d)', spoint '(0, -89d)' )   =
       sline ( spoint '(0, 90d)', spoint '(0, -89d)' )  ;
SELECT sline ( spoint '(0,  90d)', spoint '(0, -89d)' )   <>
       sline ( spoint '(0, -89d)', spoint '(0,  90d)' ) ;

