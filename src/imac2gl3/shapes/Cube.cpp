#include <cmath>
#include <vector>
#include <iostream>
#include "imac2gl3/shapes/common.hpp"
#include "imac2gl3/shapes/Cube.hpp"

namespace imac2gl3 {

void Cube::build(GLfloat size) {


/* FACE AVANT 1 */

	    //Point 1
	    m_pDataPointer[0].position.x = size*(-0.5f) ;
            m_pDataPointer[0].position.y = size*(-0.5f) ;
	    m_pDataPointer[0].position.z = size*(0.5f) ;      
            
            m_pDataPointer[0].normal.x = 0.f ;
            m_pDataPointer[0].normal.y = 0.f ;
            m_pDataPointer[0].normal.z = 1.f ;

	    m_pDataPointer[0].texCoords.x = 0.f ;
            m_pDataPointer[0].texCoords.y = 0.f;
            
           

	    //Point 2
	    m_pDataPointer[1].position.x = size*(0.5f);
            m_pDataPointer[1].position.y = size*(-0.5f);
	    m_pDataPointer[1].position.z = size*(0.5f);
            
            m_pDataPointer[1].normal.x = 0.f;
            m_pDataPointer[1].normal.y = 0.f;
            m_pDataPointer[1].normal.z = 1.f;

	    m_pDataPointer[1].texCoords.x = 0.5f;
            m_pDataPointer[1].texCoords.y = 0.f;
            
       

	    //Point 3
	    m_pDataPointer[2].position.x = size*(0.5f);
            m_pDataPointer[2].position.y = size*(0.5f);
	    m_pDataPointer[2].position.z = size*(0.5f); 
            
            m_pDataPointer[2].normal.x = 0.f;
            m_pDataPointer[2].normal.y = 0.f;
            m_pDataPointer[2].normal.z = 1.f;

	    m_pDataPointer[2].texCoords.x = 0.5f;
            m_pDataPointer[2].texCoords.y = 0.5f;
            
             

/* FACE AVANT 2 */

	    //Point 1
	    m_pDataPointer[3].position.x = size*(-0.5f);
            m_pDataPointer[3].position.y = size*(-0.5f);
	    m_pDataPointer[3].position.z = size*(0.5f);      
            
            m_pDataPointer[3].normal.x = 0.f ;
            m_pDataPointer[3].normal.y = 0.f ;
            m_pDataPointer[3].normal.z = 1.f ;

	    m_pDataPointer[3].texCoords.x = 0.f ;
            m_pDataPointer[3].texCoords.y = 0.f;
            
           

	    //Point 2
	    m_pDataPointer[4].position.x = size*(0.5f);
            m_pDataPointer[4].position.y = size*(0.5f);
	    m_pDataPointer[4].position.z = size*(0.5f);
            
            m_pDataPointer[4].normal.x = 0.f;
            m_pDataPointer[4].normal.y = 0.f;
            m_pDataPointer[4].normal.z = 1.f;

	    m_pDataPointer[4].texCoords.x = 0.5f;
            m_pDataPointer[4].texCoords.y = 0.5f;
            
       

	    //Point 3
	    m_pDataPointer[5].position.x = size*(-0.5f);
            m_pDataPointer[5].position.y = size*(0.5f);
	    m_pDataPointer[5].position.z = size*(0.5f); 
            
            m_pDataPointer[5].normal.x = 0.f;
            m_pDataPointer[5].normal.y = 0.f;
            m_pDataPointer[5].normal.z = 1.f;

	    m_pDataPointer[5].texCoords.x = 0.f;
            m_pDataPointer[5].texCoords.y = 0.5f;
            

/* FACE EST 1 */

	    //Point 1
	    m_pDataPointer[6].position.x = size*(0.5f);
            m_pDataPointer[6].position.y = size*(-0.5f);
	    m_pDataPointer[6].position.z = size*(0.5f);      
            
            m_pDataPointer[6].normal.x = 1.f ;
            m_pDataPointer[6].normal.y = 0.f ;
            m_pDataPointer[6].normal.z = 0.f ;

	    m_pDataPointer[6].texCoords.x = 0.5f ;
            m_pDataPointer[6].texCoords.y = 0.5f;
            
           

	    //Point 2
	    m_pDataPointer[7].position.x = size*(0.5f);
            m_pDataPointer[7].position.y = size*(-0.5f);
	    m_pDataPointer[7].position.z = size*(-0.5f);
            
            m_pDataPointer[7].normal.x = 1.f;
            m_pDataPointer[7].normal.y = 0.f;
            m_pDataPointer[7].normal.z = 0.f;

	    m_pDataPointer[7].texCoords.x = 1.f;
            m_pDataPointer[7].texCoords.y = 0.5f;
            
       

	    //Point 3
	    m_pDataPointer[8].position.x = size*(0.5f);
            m_pDataPointer[8].position.y = size*(0.5f);
	    m_pDataPointer[8].position.z = size*(-0.5f); 
            
            m_pDataPointer[8].normal.x = 1.f;
            m_pDataPointer[8].normal.y = 0.f;
            m_pDataPointer[8].normal.z = 0.f;

	    m_pDataPointer[8].texCoords.x = 1.f;
            m_pDataPointer[8].texCoords.y = 1.f;

/* FACE EST 2 */

	    //Point 1
	    m_pDataPointer[9].position.x = size*(0.5f);
            m_pDataPointer[9].position.y = size*(-0.5f);
	    m_pDataPointer[9].position.z = size*(0.5f);      
            
            m_pDataPointer[9].normal.x = 1.f ;
            m_pDataPointer[9].normal.y = 0.f ;
            m_pDataPointer[9].normal.z = 0.f ;

	    m_pDataPointer[9].texCoords.x = 0.5f ;
            m_pDataPointer[9].texCoords.y = 0.5f;
            
           

	    //Point 2
	    m_pDataPointer[10].position.x = size*(0.5f);
            m_pDataPointer[10].position.y = size*(0.5f);
	    m_pDataPointer[10].position.z = size*(-0.5f);
            
            m_pDataPointer[10].normal.x = 1.f;
            m_pDataPointer[10].normal.y = 0.f;
            m_pDataPointer[10].normal.z = 0.f;

	    m_pDataPointer[10].texCoords.x = 1.f;
            m_pDataPointer[10].texCoords.y = 1.f;
            
       

	    //Point 3
	    m_pDataPointer[11].position.x = size*(0.5f);
            m_pDataPointer[11].position.y = size*(0.5f);
	    m_pDataPointer[11].position.z = size*(0.5f); 
            
            m_pDataPointer[11].normal.x = 1.f;
            m_pDataPointer[11].normal.y = 0.f;
            m_pDataPointer[11].normal.z = 0.f;

	    m_pDataPointer[11].texCoords.x = 0.5f;
            m_pDataPointer[11].texCoords.y = 1.f;

/* FACE OUEST 1 */

	    //Point 1
	    m_pDataPointer[12].position.x = size*(-0.5f);
            m_pDataPointer[12].position.y = size*(-0.5f);
	    m_pDataPointer[12].position.z = size*(-0.5f);      
            
            m_pDataPointer[12].normal.x = -1.f ;
            m_pDataPointer[12].normal.y = 0.f ;
            m_pDataPointer[12].normal.z = 0.f ;

	    m_pDataPointer[12].texCoords.x = 0.5f ;
            m_pDataPointer[12].texCoords.y = 0.5f;
            
           

	    //Point 2
	    m_pDataPointer[13].position.x = size*(-0.5f);
            m_pDataPointer[13].position.y = size*(-0.5f);
	    m_pDataPointer[13].position.z = size*(0.5f);
            
            m_pDataPointer[13].normal.x = -1.f;
            m_pDataPointer[13].normal.y = 0.f;
            m_pDataPointer[13].normal.z = 0.f;

	    m_pDataPointer[13].texCoords.x = 1.f;
            m_pDataPointer[13].texCoords.y = 0.5f;
            
       

	    //Point 3
	    m_pDataPointer[14].position.x = size*(-0.5f);
            m_pDataPointer[14].position.y = size*(0.5f);
	    m_pDataPointer[14].position.z = size*(0.5f); 
            
            m_pDataPointer[14].normal.x = -1.f;
            m_pDataPointer[14].normal.y = 0.f;
            m_pDataPointer[14].normal.z = 0.f;

	    m_pDataPointer[14].texCoords.x = 1.f;
            m_pDataPointer[14].texCoords.y = 1.f;

/* FACE OUEST 2 */

	    //Point 1
	    m_pDataPointer[15].position.x = size*(-0.5f);
            m_pDataPointer[15].position.y = size*(-0.5f);
	    m_pDataPointer[15].position.z = size*(-0.5f);      
            
            m_pDataPointer[15].normal.x = -1.f ;
            m_pDataPointer[15].normal.y = 0.f ;
            m_pDataPointer[15].normal.z = 0.f ;

	    m_pDataPointer[15].texCoords.x = 0.5f ;
            m_pDataPointer[15].texCoords.y = 0.5f;
            
           

	    //Point 2
	    m_pDataPointer[16].position.x = size*(-0.5f);
            m_pDataPointer[16].position.y = size*(0.5f);
	    m_pDataPointer[16].position.z = size*(0.5f);
            
            m_pDataPointer[16].normal.x = -1.f;
            m_pDataPointer[16].normal.y = 0.f;
            m_pDataPointer[16].normal.z = 0.f;

	    m_pDataPointer[16].texCoords.x = 1.f;
            m_pDataPointer[16].texCoords.y = 1.f;
            
       

	    //Point 3
	    m_pDataPointer[17].position.x = size*(-0.5f);
            m_pDataPointer[17].position.y = size*(0.5f);
	    m_pDataPointer[17].position.z = size*(-0.5f); 
            
            m_pDataPointer[17].normal.x = -1.f;
            m_pDataPointer[17].normal.y = 0.f;
            m_pDataPointer[17].normal.z = 0.f;

	    m_pDataPointer[17].texCoords.x = 0.5f;
            m_pDataPointer[17].texCoords.y = 1.f;

/* FACE SUD 1 */

	    //Point 1
	    m_pDataPointer[18].position.x = size*(-0.5f);
            m_pDataPointer[18].position.y = size*(-0.5f);
	    m_pDataPointer[18].position.z = size*(-0.5f);      
            
            m_pDataPointer[18].normal.x = 0.f ;
            m_pDataPointer[18].normal.y = -1.f ;
            m_pDataPointer[18].normal.z = 0.f ;

	    m_pDataPointer[18].texCoords.x = 0.f ;
            m_pDataPointer[18].texCoords.y = 0.5f;
            
           

	    //Point 2
	    m_pDataPointer[19].position.x = size*(0.5f);
            m_pDataPointer[19].position.y = size*(-0.5f);
	    m_pDataPointer[19].position.z = size*(-0.5f);
            
            m_pDataPointer[19].normal.x = 0.f;
            m_pDataPointer[19].normal.y = -1.f;
            m_pDataPointer[19].normal.z = 0.f;

	    m_pDataPointer[19].texCoords.x = 0.5f;
            m_pDataPointer[19].texCoords.y = 0.5f;
            
       

	    //Point 3
	    m_pDataPointer[20].position.x = size*(0.5f);
            m_pDataPointer[20].position.y = size*(-0.5f);
	    m_pDataPointer[20].position.z = size*(0.5f); 
            
            m_pDataPointer[20].normal.x = 0.f;
            m_pDataPointer[20].normal.y = -1.f;
            m_pDataPointer[20].normal.z = 0.f;

	    m_pDataPointer[20].texCoords.x = 0.5f;
            m_pDataPointer[20].texCoords.y = 1.f;

/* FACE SUD 2 */

	    //Point 1
	    m_pDataPointer[21].position.x = size*(-0.5f);
            m_pDataPointer[21].position.y = size*(-0.5f);
	    m_pDataPointer[21].position.z = size*(-0.5f);      
            
            m_pDataPointer[21].normal.x = 0.f ;
            m_pDataPointer[21].normal.y = -1.f ;
            m_pDataPointer[21].normal.z = 0.f ;

	    m_pDataPointer[21].texCoords.x = 0.f ;
            m_pDataPointer[21].texCoords.y = 0.5f;
            
           

	    //Point 2
	    m_pDataPointer[22].position.x = size*(0.5f);
            m_pDataPointer[22].position.y = size*(-0.5f);
	    m_pDataPointer[22].position.z = size*(0.5f);
            
            m_pDataPointer[22].normal.x = 0.f;
            m_pDataPointer[22].normal.y = -1.f;
            m_pDataPointer[22].normal.z = 0.f;

	    m_pDataPointer[22].texCoords.x = 0.5f;
            m_pDataPointer[22].texCoords.y = 1.f;
            
       

	    //Point 3
	    m_pDataPointer[23].position.x = size*(-0.5f);
            m_pDataPointer[23].position.y = size*(-0.5f);
	    m_pDataPointer[23].position.z = size*(0.5f); 
            
            m_pDataPointer[23].normal.x = 0.f;
            m_pDataPointer[23].normal.y = -1.f;
            m_pDataPointer[23].normal.z = 0.f;

	    m_pDataPointer[23].texCoords.x = 0.f;
            m_pDataPointer[23].texCoords.y = 1.f;


/* FACE ARRIERE 1 */

	    //Point 1
	    m_pDataPointer[24].position.x = size*(0.5f);
            m_pDataPointer[24].position.y = size*(-0.5f);
	    m_pDataPointer[24].position.z = size*(-0.5f);      
            
            m_pDataPointer[24].normal.x = 0.f ;
            m_pDataPointer[24].normal.y = 1.f ;
            m_pDataPointer[24].normal.z = 0.f ;

	    m_pDataPointer[24].texCoords.x = 0.f ;
            m_pDataPointer[24].texCoords.y = 0.f;
            
           

	    //Point 2
	    m_pDataPointer[25].position.x = size*(-0.5f);
            m_pDataPointer[25].position.y = size*(-0.5f);
	    m_pDataPointer[25].position.z = size*(-0.5f);
            
            m_pDataPointer[25].normal.x = 0.f;
            m_pDataPointer[25].normal.y = 1.f;
            m_pDataPointer[25].normal.z = 0.f;

	    m_pDataPointer[25].texCoords.x = 0.5f;
            m_pDataPointer[25].texCoords.y = 0.f;
            
       

	    //Point 3
	    m_pDataPointer[26].position.x = size*(-0.5f);
            m_pDataPointer[26].position.y = size*(0.5f);
	    m_pDataPointer[26].position.z = size*(-0.5f); 
            
            m_pDataPointer[26].normal.x = 0.f;
            m_pDataPointer[26].normal.y = 1.f;
            m_pDataPointer[26].normal.z = 0.f;

	    m_pDataPointer[26].texCoords.x = 0.5f;
            m_pDataPointer[26].texCoords.y = 0.5f;

/* FACE ARRIERE 2 */

	    //Point 1
	    m_pDataPointer[27].position.x = size*(0.5f);
            m_pDataPointer[27].position.y = size*(-0.5f);
	    m_pDataPointer[27].position.z = size*(-0.5f);      
            
            m_pDataPointer[27].normal.x = 0.f ;
            m_pDataPointer[27].normal.y = 0.f ;
            m_pDataPointer[27].normal.z = -1.f ;

	    m_pDataPointer[27].texCoords.x = 0.f ;
            m_pDataPointer[27].texCoords.y = 0.f;
            
           

	    //Point 2
	    m_pDataPointer[28].position.x = size*(-0.5f);
            m_pDataPointer[28].position.y = size*(0.5f);
	    m_pDataPointer[28].position.z = size*(-0.5f);
            
            m_pDataPointer[28].normal.x = 0.f;
            m_pDataPointer[28].normal.y = 0.f;
            m_pDataPointer[28].normal.z = -1.f;

	    m_pDataPointer[28].texCoords.x = 0.5f;
            m_pDataPointer[28].texCoords.y = 0.5f;
            
       

	    //Point 3
	    m_pDataPointer[29].position.x = size*(0.5f);
            m_pDataPointer[29].position.y = size*(0.5f);
	    m_pDataPointer[29].position.z = size*(-0.5f); 
            
            m_pDataPointer[29].normal.x = 0.f;
            m_pDataPointer[29].normal.y = 0.f;
            m_pDataPointer[29].normal.z = -1.f;

	    m_pDataPointer[29].texCoords.x = 0.f;
            m_pDataPointer[29].texCoords.y = 0.5f;


/* FACE NORD 1 */

	    //Point 1
	    m_pDataPointer[30].position.x = size*(-0.5f);
            m_pDataPointer[30].position.y = size*(0.5f);
	    m_pDataPointer[30].position.z = size*(0.5f);      
            
            m_pDataPointer[30].normal.x = 0.f ;
            m_pDataPointer[30].normal.y = 1.f ;
            m_pDataPointer[30].normal.z = 0.f ;

	    m_pDataPointer[30].texCoords.x = 0.f ;
            m_pDataPointer[30].texCoords.y = 0.5f;
            
           

	    //Point 2
	    m_pDataPointer[31].position.x = size*(0.5f);
            m_pDataPointer[31].position.y = size*(0.5f);
	    m_pDataPointer[31].position.z = size*(0.5f);
            
            m_pDataPointer[31].normal.x = 0.f;
            m_pDataPointer[31].normal.y = 1.f;
            m_pDataPointer[31].normal.z = 0.f;

	    m_pDataPointer[31].texCoords.x = 0.5f;
            m_pDataPointer[31].texCoords.y = 0.5f;
            
       

	    //Point 3
	    m_pDataPointer[32].position.x = size*(0.5f);
            m_pDataPointer[32].position.y = size*(0.5f);
	    m_pDataPointer[32].position.z = size*(-0.5f); 
            
            m_pDataPointer[32].normal.x = 0.f;
            m_pDataPointer[32].normal.y = 1.f;
            m_pDataPointer[32].normal.z = 0.f;

	    m_pDataPointer[32].texCoords.x = 0.5f;
            m_pDataPointer[32].texCoords.y = 1.f;

/* FACE NORD 2 */

	    //Point 1
	    m_pDataPointer[33].position.x = size*(-0.5f);
            m_pDataPointer[33].position.y = size*(0.5f);
	    m_pDataPointer[33].position.z = size*(0.5f);      
            
            m_pDataPointer[33].normal.x = 0.f ;
            m_pDataPointer[33].normal.y = 1.f ;
            m_pDataPointer[33].normal.z = 0.f ;

	    m_pDataPointer[33].texCoords.x = 0.f ;
            m_pDataPointer[33].texCoords.y = 0.5f;
            
           

	    //Point 2
	    m_pDataPointer[34].position.x = size*(0.5f);
            m_pDataPointer[34].position.y = size*(0.5f);
	    m_pDataPointer[34].position.z = size*(-0.5f);
            
            m_pDataPointer[34].normal.x = 0.f;
            m_pDataPointer[34].normal.y = 1.f;
            m_pDataPointer[34].normal.z = 0.f;

	    m_pDataPointer[34].texCoords.x = 0.5f;
            m_pDataPointer[34].texCoords.y = 1.f;
            
       

	    //Point 3
	    m_pDataPointer[35].position.x = size*(-0.5f);
            m_pDataPointer[35].position.y = size*(0.5f);
	    m_pDataPointer[35].position.z = size*(-0.5f); 
            
            m_pDataPointer[35].normal.x = 0.f;
            m_pDataPointer[35].normal.y = 1.f;
            m_pDataPointer[35].normal.z = 0.f;

	    m_pDataPointer[35].texCoords.x = 0.f;
            m_pDataPointer[35].texCoords.y = 1.f;


    }

}
