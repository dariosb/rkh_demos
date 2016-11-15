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

/* ------------------------------ Description ------------------------------ */
    Plaforms supported:
    ------------------

     Linux    - GCC
     Windows  - VisualStudio 2010/2012
     EduCIAA  - CiaaIDE Windows / Linux
     FrdmK64F - Kinetis Design Studio

    RKH Demos:
    ---------
    demos\
    x-- blinky_educiaa      - RKH blinky demo, CIAA struct like (no-cross)
    x-- cross\              - cross platform demos
    |   `---- blinky\       - RKH blinky demo for all supported platforms
    |         `-----arch\   - platform specific bsp's makefiles and projects
    x-------- shared\       - RKH shared demo for all supported platforms
    |         `---- arch\   - platform specific bsp's makefiles and projects
    x-- oven\               - RKH Oven demos
        `-- arch\           - platform specific bsp's makefiles and projects
        `-- model\          - Papyrus Oven1-4 UML Models
        `-- oven1-4         - RKH app


/* ==================== EduCIAA RKH Demos build guide ====================== */
    This demos use Firmware_UPA-1.0.0 release, download from:
    < https://github.com/ciaa/Firmware/releases/tag/1.0.0 >
    Install this Demo Package at same level of CIAA Firmware repository.
    ej in windows: c:/CIAA/.

/* From Linux Terminal */
 - open terminal at ./CIAA/Firmware_UPA-1.0.0
 - export BOARD=edu_ciaa_nxp
 - Set PROJECT_PATH
  1-blinky_educiaa: 
     export PROJECT_PATH=../rkhwshop/demos/blinky_educiaa/
  2-blinky:
     export PROJECT_PATH=../rkhwshop/demos/cross/blinky/arch/fosek/educiaa/
  3-shared:
     export PROJECT_PATH=../rkhwshop/demos/cross/shared/arch/fosek/educiaa/
  4-oven demos: 
     export PROJECT_PATH=../rkhwshop/demos/oven/arch/educiaa/
    and select oven demo { X: 1 - 4 }:
     export OVEN_APP_IX=ovenX   

/* From CiaaIDE */
 - Import projects to CiaaIDE (Windows or Linux)

/* ==================== FrdmK64F RKH Demos build guide ===================== */
 - Must provide Kinetis SDK (KSDK) V1.2 
 - Import projects to NXP/Fresscale Kinetis Development Studio (KDS)

/* ==================== Windows RKH Demos build guide ====================== */
 - Use Visual Studio Express 2010/2012
 - Open projects into "arch/..." folders of each demo

/* ===================== Linux RKH Demos build guide ======================= */
 - Open terminal in Use Visual Studio Express 2010/2012
 - Open projects into "arch/..." folders of each demo

/* ------------------------------ End of file ------------------------------ */
