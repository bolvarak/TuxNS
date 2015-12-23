## Helpers
if(NOT WIN32)
	string(ASCII 27 Esc)
	set(ColorReset  "${Esc}[m")
	set(ColorBold   "${Esc}[1m")
	set(Red         "${Esc}[31m")
	set(Green       "${Esc}[32m")
	set(Yellow      "${Esc}[33m")
	set(Blue        "${Esc}[34m")
	set(Magenta     "${Esc}[35m")
	set(Cyan        "${Esc}[36m")
	set(White       "${Esc}[37m")
	set(BoldRed     "${Esc}[1;31m")
	set(BoldGreen   "${Esc}[1;32m")
	set(BoldYellow  "${Esc}[1;33m")
	set(BoldBlue    "${Esc}[1;34m")
	set(BoldMagenta "${Esc}[1;35m")
	set(BoldCyan    "${Esc}[1;36m")
	set(BoldWhite   "${Esc}[1;37m")
endif()

## CMake Policy
cmake_policy(SET CMP0005 NEW)

## GeoIP Locations
set(GeoIP_Data_Dir         "/usr/share/GeoIP") ## System Installed GeoIP Database Directory
set(GeoIP_Package_Version  "1.6.3")            ## GeoIP Package Version (Don't Change)
set(GeoIP_v4_CityDB       "/usr/share/GeoIP/GeoLiteCity.dat")   ## GeoIP IPv4 City Database
set(GeoIP_v6_CityDB       "/usr/share/GeoIP/GeoLiteCityv6.dat") ## GeoIP IPv6 City Database
set(GeoIP_v4_ISPDB        "/usr/share/GeoIP/GeoIPASNum.dat")    ## GeoIP IPv4 ISP Database
set(GeoIP_v6_ISPDB        "/usr/share/GeoIP/GeoIPASNumv6.dat")  ## GeoIP IPv6 ISP Database

## HeimdallGI File Paths
set(HGI_Config_File       "${CMAKE_CURRENT_LIST_DIR}/../api/application.ini")
set(HGI_Static_Files      "${CMAKE_CURRENT_LIST_DIR}/../../htdocs")
set(HGI_Views             "${CMAKE_CURRENT_LIST_DIR}/../api/views")

## TuxNS Database Settings
set(Tux_DB_Driver         "QPSQL")     ## TuxNS Database Driver (Don't Change)
set(Tux_DB_Server         "localhost") ## TuxNS Dabase Server
set(Tux_DB_Port           "5432")      ## TuxNS Database Port
set(Tux_DB_Name           "tuxns")     ## TuxNS Database Name
set(Tux_DB_User           "tuxns")     ## TuxNS Database Username
set(Tux_DB_Pass           "changeMe")  ## TuxNS Database Password

## Normalize File Paths
execute_process(COMMAND realpath -z ${GeoIP_v4_CityDB}  OUTPUT_VARIABLE GeoIP_v4_CityDB)
execute_process(COMMAND realpath -z ${GeoIP_v6_CityDB}  OUTPUT_VARIABLE GeoIP_v6_CityDB)
execute_process(COMMAND realpath -z ${GeoIP_v4_ISPDB}   OUTPUT_VARIABLE GeoIP_v4_ISPDB)
execute_process(COMMAND realpath -z ${GeoIP_v6_ISPDB}   OUTPUT_VARIABLE GeoIP_v6_ISPDB)
execute_process(COMMAND realpath -z ${HGI_Config_File}  OUTPUT_VARIABLE HGI_Config_File)
execute_process(COMMAND realpath -z ${HGI_Static_Files} OUTPUT_VARIABLE HGI_Static_Files)
execute_process(COMMAND realpath -z ${HGI_Views}        OUTPUT_VARIABLE HGI_Views)

## Definitions
add_definitions(
	-DGEOIPDATADIR="${GeoIP_Data_Dir}"
	-DPACKAGE_VERSION="${GeoIP_Package_Version}"
	-DGEOIP_CITY_DB="${GeoIP_v4_CityDB}"
	-DGEOIP_CITYv6_DB="${GeoIP_v6_CityDB}"
	-DGEOIP_ISP_DB="${GeoIP_v4_ISPDB}"
	-DGEOIP_ISPv6_DB="${GeoIP_v6_ISPDB}"
	-DHGI_CONFIG_FILE="${HGI_Config_File}"
	-DHGI_STATIC_FILES="${HGI_Static_Files}"
	-DHGI_VIEWS="${HGI_Views}"
	-DTUXNS_DB_DRIVER="${Tux_DB_Driver}"
	-DTUXNS_DB_HOST="${Tux_DB_Server}"
	-DTUXNS_DB_PORT="${Tux_DB_Port}"
	-DTUXNS_DB="${Tux_DB_Name}"
	-DTUXNS_DB_USER="${Tux_DB_User}"
	-DTUXNS_DB_PASS="${Tux_DB_Pass}"
)

## Output
message("${Red}GeoIP System Directory: ${ColorReset}  ${Cyan}${GeoIP_Data_Dir} (${GeoIP_Package_Version})${ColorReset}")
message("${Red}GeoIPv4 City Database:  ${ColorReset}  ${Cyan}${GeoIP_v4_CityDB}${ColorReset}")
message("${Red}GeoIPv6 City Database:  ${ColorReset}  ${Cyan}${GeoIP_v6_CityDB}${ColorReset}")
message("${Red}GeoIPv4 ISP Database:   ${ColorReset}  ${Cyan}${GeoIP_v4_ISPDB}${ColorReset}")
message("${Red}GeoIPv6 ISP Database:   ${ColorReset}  ${Cyan}${GeoIP_v6_ISPDB}${ColorReset}")
message("${Red}HeimdallGI Config File: ${ColorReset}  ${Cyan}${HGI_Config_File}${ColorReset}")
message("${Red}HeimdallGI Static Files:${ColorReset}  ${Cyan}${HGI_Static_Files}${ColorReset}")
message("${Red}HeimdallGI View Files:  ${ColorReset}  ${Cyan}${HGI_Views}${ColorReset}")

## CMake Minimum Version
cmake_minimum_required(VERSION 3.2)

## Project Definition
project(TuxNS)

## CMake Settings & Configuration
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11")

## Source Headers & Files
set(SOURCE_FILES
	../api/externals/HeimdallGI/CGI.h
	../api/externals/HeimdallGI/Configuration.h
	../api/externals/HeimdallGI/DBI.h
	../api/externals/HeimdallGI/ErrorController.h
	../api/externals/HeimdallGI/HTML.h
	../api/externals/HeimdallGI/Log.h
	../api/externals/GeoIP/libGeoIP/GeoIP_internal.h
	../api/externals/GeoIP/libGeoIP/GeoIP.h
	../api/externals/GeoIP/libGeoIP/GeoIPCity.h
	../api/externals/HeimdallGI/MaxMind.h
	../api/externals/HeimdallGI/Router.h
	../api/externals/HeimdallGI/Template.h
	../api/externals/HeimdallGI/View.h
	../api/controllers/GeoIP.h
	../api/main.cpp
	../api/externals/HeimdallGI/CGI.cpp
	../api/externals/HeimdallGI/Configuration.cpp
	../api/externals/HeimdallGI/DBI.cpp
	../api/externals/HeimdallGI/ErrorController.cpp
	../api/externals/HeimdallGI/HTML.cpp
	../api/externals/HeimdallGI/Log.cpp
	../api/externals/GeoIP/libGeoIP/timeZone.c
	../api/externals/GeoIP/libGeoIP/regionName.c
	../api/externals/GeoIP/libGeoIP/GeoIP_deprecated.c
	../api/externals/GeoIP/libGeoIP/GeoIP.c
	../api/externals/GeoIP/libGeoIP/GeoIPCity.c
	../api/externals/HeimdallGI/MaxMind.cpp
	../api/externals/HeimdallGI/Router.cpp
	../api/externals/HeimdallGI/Template.cpp
	../api/externals/HeimdallGI/View.cpp
	../api/controllers/GeoIP.cpp
)

## Automoc
set(CMAKE_AUTOMOC ON)

## Qt5 Packages
find_package(Qt5Core)
find_package(Qt5Network)
find_package(Qt5Sql)
find_package(Qt5Xml)

## Executable
add_executable(tux.cgi ${SOURCE_FILES})

## Links
target_link_libraries(tux.cgi Qt5::Core Qt5::Network Qt5::Sql)
