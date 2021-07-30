Um die Funktionen zu testen, können verschiedene Parameter übergeben werden.

./Robot -export

--> Exportiert die genutzten PwmChips. Dieser Befehl muss einmalig nach jedem Bootvorgang des Beaglebones ausgeführt werden


./Robot -forward [speed] [distance]

--> speed 		- 		ist das prozentuale Pulsweitenverhältnis [0-100]. Die Motoren drehen in einem Bereich von 10-90
--> distance  	-		ist die zu fahrenede Strecke in cm


./Robot -backward [speed] [distance]

--> speed 		- 		ist das prozentuale Pulsweitenverhältnis [0-100]. Die Motoren drehen in einem Bereich von 10-90
--> distance  	-		ist die zu fahrenede Strecke in cm


./Robot -angle [winkel] [directionOfRotation]				-- 			lässt den Motor um sich selbst drehen

--> winkel 					- 		ist der Winkel der gefahren werden soll
--> directionOfRotation  	-		Drehrichtungsangabe: "-cw"  "-ccw"


./Robot -circula [direction] [directionOfRotation] [radius] [winkel]					-- 			soll den Roboter kreisförmig fahren lassen

--> direction 				-		Fahrtrichtungsangabe: "-forward" "-backward"
--> directionOfRotation		-		Drehrichtungsangabe: "-cw"  "-ccw"
--> radius					-		Radius des Kreisbogens
--> winkel					-		Winkel des Kreisbogens




./Robot -servo			--			lässt den Servo in einer Sequenz beispielhaft drehen