# Stauffer Library Seat Checker
*This project was created for the P2 project for APSC200 at Queen's Unviersity.*  
The purpose of the project is to conceptualize a live seat map for Joseph S. Stauffer Library.  
  
The hardware portion consists of the following:  
- Arduino Uno Wifi Rev2
- PIR Motion Sensor
- Film Pressure Sensor
  

When _both_ motion and pressure are sensed at a table, the website will update to reflect the presence of a person by displaying a red circle  
When _either_ motion or pressure are sensed at a table, the website will update to reflect *possible* presence of a person by displaying a yellow circle  
When _neither_ motion nor pressure are sensed at a table, the website will update to reflect no presense of a person by displaying a green circle  
