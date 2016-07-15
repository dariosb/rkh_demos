/**
 *  \file       readme
 *  \brief      RKH demos for SASE2016 workshop 
 */
/* -------------------- RKH demos for SASE2016 workshop -------------------- */
/* -------------------------- Development history -------------------------- */
/*
 *  2016.03.17  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Darío Baliña  dariosb@gmail.com
 */

\reads

Platforms supported:
 Linux    - GCC
 Windows  - VisualStudio 2010/2012
 EduCIAA  - CiaaIDE Windows / Linux
 FrdmK64F - Kinetis Design Studio

demos\
    blinky_educiaa      - RKH blinky demo, CIAA struct like (no-cross)
    cross\              - cross platform demos
          blinky\       - RKH blinky demo for all supported platforms
                arch\   - platform specific bsp's makefiles and projects
          shared\       - RKH shared demo for all supported platforms
                arch\   - platform specific bsp's makefiles and projects
    oven\               - RKH Oven demos
        arch\           - platform specific bsp's makefiles and projects
        model\          - Papyrus Oven1-4 UML Models
        oven1-4         - RKH app

/* ------------------------------ End of file ------------------------------ */
