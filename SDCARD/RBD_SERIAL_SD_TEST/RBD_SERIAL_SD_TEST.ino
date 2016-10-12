// Arduino RBD usb Manager Library v1.0.0-alpha.3 Example - Control the built-in Arduino led with usb commands: on off pwm,255
// https://github.com/alextaujenis/RBD_usbManager
// Copyright 2016 Alex Taujenis
// MIT License

// include the SD library:
#include <SPI.h>
#include <SD.h>

/*
 * Ajustar monitor serial con \n al final
 */
#include <RBD_SerialManager.h> // https://github.com/alextaujenis/RBD_usbManager

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
File file;

RBD::SerialManager usb;

void setup() {
  usb.start();
  usb.println(F("INICIO"));
  if (!SD.begin(4)) {
    usb.println("ERROR en SD");
    return;
  }
}

void loop() {

  // you must set the usb monitor to include a newline with each command
  if (usb.onReceive()) {

    // abre archivo
    if (usb.isCmd("open")) {
      usb.println(usb.getCmd());
      String nombre = usb.getParam();
      usb.println(nombre);
      file = SD.open(nombre, FILE_WRITE);
      if (file) {
        usb.println(">>>");
      } else {
        usb.println(F("ERROR open"));
        return;
      }
    }

    // escribe archivo
    if (usb.isCmd("write")) {
      usb.println(usb.getCmd());
      String texto = usb.getParam();
      if(file){
      file.println(texto);
      usb.println(texto);
      }else{
        usb.println(F("ERROR no abierto"));
      }
    }

    // cierra archivo
    if (usb.isCmd("close")) {
      usb.println(usb.getCmd());
      file.close();
      delay(100); //SD ejecuta además un flush
      usb.println("<<<");
    }

    // elimina archivo
    if (usb.isCmd("delete")) {
      usb.println(usb.getCmd());
      String texto = usb.getParam();
      if(SD.remove(texto)){
        usb.println(texto);
      }else{
        usb.println(F("ERROR eliminar"));
      }
    }
    
    //lista archivos de la tarjeta SD
    if (usb.isCmd("dir")) {
      usb.println(usb.getCmd());
      usb.println("***");
      File midir = SD.open("/");
      if (midir)
      {
        printDirectory(midir, 0);
        midir.close();
      }
      else {
        usb.println(F("ERROR Directorio"));
      }
      usb.println("***");

    }

    //muestra contenido de un archivo
    if (usb.isCmd("dump")) {
      usb.println(usb.getCmd());
      String nombre = usb.getParam();
      usb.println(nombre);
      usb.println("***");
      file = SD.open(nombre);

      // if the file is available, read from it:
      if (file) {
        while (file.available()) {
          usb.print((char)file.read());
        }
        file.close();
      }
      // if the file isn't open, pop up an error:
      else {
        usb.println(F("ERROR archivo"));
      }
      usb.println("***");
    }

    // caracteristicas de la tarjeta SD
    if (usb.isCmd("sd")) {

      usb.print("\nInicia SD: ");

      // we'll use the initialization code from the utility libraries
      // since we're just testing if the card is working!
      if (!card.init(SPI_HALF_SPEED, 4)) {
        usb.println(F("Fallo"));
        return;
      } else {
        usb.println("ok");
      }

      // print the type of card
      usb.print(F("\nTipo: "));
      switch (card.type()) {
        case SD_CARD_TYPE_SD1:
          usb.println("SD1");
          break;
        case SD_CARD_TYPE_SD2:
          usb.println("SD2");
          break;
        case SD_CARD_TYPE_SDHC:
          usb.println("SDHC");
          break;
        default:
          usb.println("?");
      }

      // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
      if (!volume.init(card)) {
        usb.println(F("Falta FAT16/FAT32"));
        return;
      }


      // print the type and size of the first FAT-type volume
      uint32_t volumesize;
      usb.print("\nFAT ");
      usb.println(volume.fatType());
      usb.println("");

      volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
      volumesize *= volume.clusterCount();       // we'll have a lot of clusters
      volumesize *= 512;                            // SD card blocks are always 512 bytes
      usb.print("Tamaño (bytes): ");
      usb.println(volumesize);
    }
  }
}

void printDirectory(File dir, int numTabs) {
  dir.rewindDirectory();
  
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      dir.rewindDirectory();
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      usb.print('\t');
    }
    usb.print(entry.name());
    if (entry.isDirectory()) {
      usb.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      usb.print("\t\t");
      usb.println(entry.size());
    }
    entry.close();
  }
}
