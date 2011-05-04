#include <argos2/common/utility/math/shapes2/circle.h>
#include <argos2/common/utility/math/shapes2/rectangle.h>
#include <argos2/common/utility/math/shapes2/compound.h>

/****************************************/
/****************************************/

argos::SIntersectionData2 idCircleCompound, idCompoundCircle;
argos::UInt32 counter = 0;

/****************************************/
/****************************************/

void StartGnuplot() {
   std::cout << "set term x11 size 640,640" << std::endl;
   std::cout << "set size square" << std::endl;
   std::cout << "set xrange [-5:5]" << std::endl;
   std::cout << "set yrange [-5:5]" << std::endl;
   std::cout << "set grid xtics ytics layerdefault" << std::endl;
   std::cout << "unset key" << std::endl;   
   std::cout << "set xtics border mirror out 1.0" << std::endl;
   std::cout << "set x2tics border mirror out 1.0" << std::endl;
   std::cout << "set ytics border mirror out 1.0" << std::endl;
   std::cout << "set y2tics border mirror out 1.0" << std::endl;
   std::cout << "unset mouse" << std::endl;
   std::cout << "set title '" << counter << ", Circle->Compound " << std::boolalpha << idCircleCompound.Intersection << ",Compound->Circle " << idCompoundCircle.Intersection << "'" << std::endl;
   std::cout << "set multiplot" << std::endl;
}

/****************************************/
/****************************************/

void StopGnuplot() {
   std::cout << "unset multiplot" << std::endl;   
}

/****************************************/
/****************************************/

int main() {

	typedef std::vector<argos::CPrimitive2*> TChildren;
	typedef std::vector<argos::CPrimitive2*>::iterator TIteratorChildren;

   //argos::CRectangle r(argos::CVector2(0.5, -1.0), argos::CRadians::PI_OVER_TWO, 2.0, 1.0);
	argos::CRectangle r(argos::CVector2(0.5, -0.5), argos::CRadians::PI, 2.0, 1.0);

	argos::CRectangle r2(argos::CVector2(-1, -0.5), argos::CRadians::ZERO, 2.0, 1.0);
  argos::CCircle c(argos::CVector2(0.5, -2.5), 0.5);
   argos::CCircle circle(argos::CVector2(0.5, 1.3), 1.0);
   argos::CRectangle rect(argos::CVector2(0.5, 1.5), argos::CRadians::PI_OVER_THREE, 2.0, 1.0);
   argos::CCompound compound(argos::CVector2(0.5, -1.0));
   compound.AddChild(&r);
   compound.AddChild(&r2);
   compound.AddChild(&c);

   TChildren m_tChildren = compound.GetChildren();

   //compound.Rotate(argos::CRadians::PI/9);
   //compound.AddChild(&c);


   for (counter = 0; counter < 20; ++counter){
	   //r.Intersects(idRC, c);
	   //c.Intersects(idCR, r);

//	   circle.Intersects(idCircleCompound, r);
//	   r.Intersects(idCompoundCircle, circle);

	   rect.Intersects(idCircleCompound, r);
	   r.Intersects(idCompoundCircle, rect);


	   //rect.Intersects(idCircleCompound, r);
	   //r.Intersects(idCompoundCircle, rect);
	   //rect.Intersects(idCircleCompound, compound);
	   //compound.Intersects(idCompoundCircle, rect);

	   //circle.Intersects(idCircleCompound, compound);
	   //compound.Intersects(idCompoundCircle, circle);

	   //r.Gnuplot();


	   StartGnuplot();

	   rect.Gnuplot();
	   r.Gnuplot();
	   //circle.Gnuplot();
	   //compound.Gnuplot();

	   StopGnuplot();
	   std::cin.get();
	   //compound.Rotate(argos::CRadians::PI/9);
	   r.Rotate(argos::CRadians::PI/9);

   }





}
