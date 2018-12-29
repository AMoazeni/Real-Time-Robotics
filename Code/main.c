// Main Function
void main(){

  // Initialize Function
  INZfunction();

  // Control System Loop - Stop Operation With Software or E-Button Hardware
  while(OperationMode != 0  &&  !EmergencyButton){

      // If Diagnostics Succeed
      if (diagnostics()){

          MSSfunction();  // Machine Status Scan
          MCSfunction();  // Mode Control Supervisor
          OCSfunction();  // User Interface Output

      }


      // If Diagnostics Fail - Run Error Treatment
      else{

          ERHfunction();  // Error Treatment
          OCSfunction();  // User Interface Output

      } // End Diagnostics

    } // End Control System Loop

} // End Main
