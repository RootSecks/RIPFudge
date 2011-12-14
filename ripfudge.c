/*
RIP Fudge - The Routing Information Protocol Fudger :)

Copyright 2011, 2012 Andrew Railton

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.    
*/





#include<stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

struct ripdatagram {
	
	//RIP Header
	uint8_t headerone; //command
	uint8_t headertwo; //version
	uint8_t headerthree; //zero byte
	uint8_t headerfour; //zero byte
	
	//here the route entry starts for RIPv1, or is authentication  for RIPv2
	uint8_t byteone; //RIPv2 fullbyte, RIPv1 address family first byte 
	uint8_t bytetwo; //RIPv2 fullbyte, RIPv2 address family
	uint8_t bytethree; //RIPv2 Auth Type
	uint8_t bytefour; //RIPv2 Auth Type
	
	uint8_t bytefive; //RIPv2 password
	uint8_t bytesix; //RIPv2 password
	uint8_t byteseven; //RIPv2 password
	uint8_t byteeight; //RIPv2 password
	
	uint8_t bytenine; //RIPv2 password
	uint8_t byteten; //RIPv2 password
	uint8_t byteeleven; //RIPv2 password
	uint8_t bytetwelve; //RIPv2 password
	
	uint8_t bytethirteen; //RIPv2 password
	uint8_t bytefourteen; //RIPv2 password
	uint8_t bytefifteen; //RIPv2 password
	uint8_t bytesixteen; //RIPv2 password
	
	uint8_t byteseventeen; //RIPv2 password
	uint8_t byteeighteen; //RIPv2 password
	uint8_t bytenineteen; //RIPv2 password
	uint8_t bytetwenty; //RIPv2 password
	
	//Here the route entry for RIPv2 beginds
	uint8_t bytetwentyone; //RIPv2 Address Family
	uint8_t bytetwentytwo; //RIPv2 Address Family
	uint8_t bytetwentythree; //RIPv2 Route Tag
	uint8_t bytetwentyfour; //RIPv2 Route Tag
	
	uint8_t bytetwentyfive; //RIPv2 IP Byte One
	uint8_t bytetwentysix; //RIPv2 IP Byte Two
	uint8_t bytetwentyseven; //RIPv2 IP Byte Three
	uint8_t bytetwentyeight; //RIPv2 IP Byte Four
	
	uint8_t bytetwentynine; //RIPv2 Subnet Byte One
	uint8_t bytethirty; //RIPv2 Subnet Byte Two
	uint8_t bytethirtyone; //RIPv2 Subnet Byte Three
	uint8_t bytethirtytwo; //RIPv2 Subnet Byte Four
	
	uint8_t bytethirtythree; //RIPv2 Next Hop One
	uint8_t bytethirtyfour; //RIPv2 Next Hop Two
	uint8_t bytethirtyfive; //RIPv2 Next Hop Three
	uint8_t bytethirtysix; //RIPv2 Next Hop Four
	
	uint8_t bytethirtyseven; //RIPv2 Metric One
	uint8_t bytethirtyeight; //RIPv2 Metric Two
	uint8_t bytethirtynine; //RIPv2 Metric Three
	uint8_t byteforty; //RIPv2 Metric Four

	
};


void packet_renderer ( char dgramrender[] , char* targetdest) {
	
	int g;
	
	printf(" \r\n---Packet Render----\r\n" );
	printf(" Target: %s\r\n" , targetdest);
	printf("--------------------\r\n\r\n" );
	

}


//MAIIIINNNNNNNNNN( Get those args)
int main( int argc, char *argv[] ) {

	//Initalize the addr struct
	struct sockaddr_in destaddr;
	
	//Init and define the string for the destination IP address
	char* dstipaddr = "127.0.0.1";
	
	//Init and define the port (520 for RIP)
	int protoport = 520;
	
	//Init (And define by default) a variable for the sock
	int udpsock;
	//Init and define a variable for the return from the sendto function
	int sendsock;
	
	//Send Test Variable
	int sendtest;
		
	//Init and Define the size of the struct
	size_t sizeofstruct;
	
	//Verbose Variable
	int verboseflag = 0;
	
	//If there is less than 2 arguments
	if (argc < 2) {
		
		//Title
		printf( "\r\nRIP FUDGE\r\n" );
		printf( "<(-'.'-<) (>-'.'-)>\r\n" );
		
		//Explain the application
		printf("\r\nDescription:\r\n\r\n" );
		printf("	RIPFuge is a simple application that can be used \r\n" );
		printf("	to generate RIP (Routing Information Protocol) Datagrams.\r\n\r\n" );
		printf("	The Routing Information Protocol is a routing protocol used\r\n" );
        	printf("	to propergate routes around a network. In it's earliest\r\n" );
        	printf("	implementation routers would spam the network with\r\n" );
        	printf("	\"updates\" that contained all the routes in their routing table.\r\n" );
        	printf("	Later versions of the protocol added authentication as well as\r\n" );
        	printf("	classlessness (Subnetting) and request/response route updates.\r\n" );
        	printf("	It is the simplest routing protocol, however due to the fact\r\n" );
       		printf("	that it is extremley easy to use, it is still fairly prevelant.\r\n" );
		
		
		//Explain the Usage
		printf( "\r\nUsage: \r\n\r\n" );
		printf( "	%s [ -aAVvcrsnNpmt ]\r\n" , argv[0]);
		printf( "		[ -a Address Family ]\r\n" );
		printf( "		[ -A Authentication Type ]\r\n" );
		printf( "		[ -v Version ]\r\n" );
		printf( "		[ -c Command ]\r\n" );
		printf( "		[ -r Route Tags ]\r\n" );
		printf( "		[ -s Subnet Mask ]\r\n" );
		printf( "		[-n Network IP Address (Destination Network) ]\r\n" );
		printf( "		[ -N Next Hop ]\r\n" );
		printf( "		[ -p Password ]\r\n" );
		printf( "		[ -m Metric (Hops) ]\r\n" );
		printf( "		[ -t Target (Usually either Router IP or Subnet Broadcast Address) ]\r\n" );

		//Explain the flags
		printf("\r\nOptions: \r\n\r\n" );
		printf("	Address Family: This is the Network Layer Protocol.etc\r\n\r\n" );
		printf("	Authentication Type: Type of authentication securing\r\n" );
		printf("		RIP on the target router(s).\r\n\r\n" );
		printf("	Version: This is the RIP version. RIPv1 or RIPv2.\r\n\r\n" );
		printf("	Verbose: Display verbose program messages. \r\n\r\n" );
		printf("	Command: This is the RIP Command value, 2 for Response.\r\n\r\n" );
		printf("	Route Tags: Optional Route Tags for RIPv2\r\n\r\n" );
		printf("	Subnet Mask: The subnet mask is used to determine the host \r\n" );
		printf("		and network parts of the Network IP Address.\r\n\r\n" );
		printf("	Network IP Address: The IP Address of the network \r\n" );
		printf("		you are descriping a route to.\r\n\r\n" );
		printf("	Next Hop: This is the IP Address of the router which you \r\n" );
		printf("		want the route to point to.\r\n\r\n" );
		printf("	Password: In the case of auth type 2, this will hold the \r\n" );
		printf("		plain text password.\r\n\r\n" );
		printf("	Metric: The metric for RIP is \"hop count\". Which is the number of \r\n" );
		printf("		routers between the target and the network.\r\n" );
		printf("	Target: This will be the IP that the packet is send to \r\n" );
		printf("		usually either a router, or a broadcast address. \r\n" );
		
	//Otherwise
	} else {
		
		
		//Title
		printf( "\r\nRIP FUDGE\r\n" );
		printf( "<(-'.'-<) (>-'.'-)>\r\n\r\n" );
			
		//Init and Define a buffer to hold the RIP Header
		char headerbuf[4096];
	
		//Attatch it to the ripdgram struct
		struct ripdatagram *ripheader = ( struct ripdatagram * ) headerbuf;
	
		//Fill the memory for the RIP Header
		memset (headerbuf, 0, 4096);

		
		//Initalize variables for hte header
		unsigned int command;
		unsigned int authtype;
		unsigned int version;
		
		unsigned int addrfamily;
		unsigned int routetag;
	
		
		unsigned int netip[3];
		
		unsigned int subnetmask[3];
		
		unsigned int nexthopip[3];
		
		unsigned int metric[3];
		
		unsigned int passwordint[15];

		//Set Defauilts
		command = 2;
		version = 1;
		addrfamily = 2;
		authtype = 2;
		routetag = 0;

		netip[0] = 192;
		netip[1] = 168;
		netip[2] = 0;
		netip[3] = 1;
		
		subnetmask[0] = 255;
		subnetmask[1] = 255;
		subnetmask[2] = 255;
		subnetmask[3] = 0;
		
		nexthopip[0] = 192;
		nexthopip[1] = 168;
		nexthopip[2] = 0;
		nexthopip[3] = 1;
		
		metric[0] = 0;
		metric[1] = 0;
		metric[2] = 0;
		metric[3] = 1;
		
		//Passwords Defaults
		passwordint[0] = 0;
		passwordint[1] = 0;
		passwordint[2] = 0;
		passwordint[3] = 0;
		passwordint[4] = 0;
		passwordint[5] = 0;
		passwordint[6] = 0;
		passwordint[7] = 0;
		passwordint[8] = 0;
		passwordint[9] = 0;
		passwordint[10] = 0;
		passwordint[11] = 0;
		passwordint[12] = 0;
		passwordint[13] = 0;
		passwordint[14] = 0;
		passwordint[15] = 0;
		
		int i;
		int x;
			
		
		
		//Sort out the cmd line args		
		for ( i = 1; i < argc; i++ ) {
			
			//Check for Address Family flag
			if ( strcmp( argv[i] , "-a" ) == 0 ) {
			
				switch( atoi( argv[i+1] ) ) {
					case 1:
						addrfamily = 1;
						break;
					default:
						addrfamily = 2;
						break;
				}
				
			}
			
			//Check for authtype flag
			if ( strcmp( argv[i] , "-A" ) == 0 ) {
			
				switch( atoi( argv[i+1] ) ) {
					case 1:
						authtype = 1;
						break;
					default:
						authtype = 2;
						break;
				}			
			}
			
			//Check for Version			
			if ( strcmp( argv[i] , "-v" ) == 0 ) {
			
				switch( atoi( argv[i+1] ) ) {
					case 2:
						version = 2;
						break;
					case 1:
						version = 1;
						break;
					default:
						version = 1;
						break;
				}					
			}
			
			//Check for Version			
			if ( strcmp( argv[i] , "-V" ) == 0 ) {
			
				verboseflag = 1;
				
			}

			//Check for Command			
			if ( strcmp( argv[i] , "-c" ) == 0 ) {
			
				switch( atoi( argv[i+1] ) ) {
					case 1:
						command = 1;
						break;
					case 2:
						command = 2;
						break;
					case 3:
						command = 3;
						break;
					default:
						command = 2;
						break;
				}					
			}
			
			//Check for Route Tags
			if ( strcmp( argv[i] , "-r" ) == 0 ) {
			
				switch( atoi( argv[i+1] ) ) {
					default:
						routetag = 0;
						break;
				}
				
			}
			
			//Check for Subnet Mask
			if ( strcmp( argv[i] , "-s" ) == 0 ) {
				
				char *subnetptr = strtok( argv[i + 1] , "." );
			
				subnetmask[0] = atoi( subnetptr );
				
				subnetptr = strtok( NULL , "." );
				
				subnetmask[1] = atoi( subnetptr );
			
				subnetptr = strtok( NULL , "." );
				
				subnetmask[2] = atoi( subnetptr );
				
				subnetptr = strtok( NULL , "\0" );
				
				subnetmask[3] = atoi( subnetptr );
				
				
			}
			
			//Check for Network IP
			if ( strcmp( argv[i] , "-n" ) == 0 ) {
				
				char *ipptr = strtok( argv[i + 1] , "." );
			
				netip[0] = atoi( ipptr );
				
				ipptr = strtok( NULL , "." );
				
				netip[1] = atoi( ipptr );
			
				ipptr = strtok( NULL , "." );
				
				netip[2] = atoi( ipptr );
				
				ipptr = strtok( NULL , "\0" );
				
				netip[3] = atoi( ipptr );
				
			}
			
			//Check for next hop IP
			if ( strcmp( argv[i] , "-N" ) == 0 ) {
				
				char *nexthopptr = strtok( argv[i + 1] , "." );
			
				nexthopip[0] = atoi( nexthopptr );
				
				nexthopptr = strtok( NULL , "." );
				
				nexthopip[1] = atoi( nexthopptr );
			
				nexthopptr = strtok( NULL , "." );
				
				nexthopip[2] = atoi( nexthopptr );
				
				nexthopptr = strtok( NULL , "\0" );
				
				nexthopip[3] = atoi( nexthopptr );
				
			}
			
			//Check for password
			if ( strcmp( argv[i] , "-p" ) == 0 ) {
				
				
				
			}
			
			//Check for metric
			if ( strcmp( argv[i] , "-m" ) == 0 ) {
				
				//METRIC!!!
				metric[3] = atoi( argv[i+1] );
				
			}
			
			//Check for target
			if ( strcmp( argv[i] , "-t" ) == 0 ) {
				
				dstipaddr = argv[i + 1];
				
			}
			
		}
		
		
		printf( "\r\nVersion %i\r\n" , version );
		
		
	
		//Build the RIP Header by defining the various variables in the struct		
		if (version == 2) {
			ripheader->headerone = command; //Command 
			ripheader->headertwo = version; //RIP Version
			ripheader->headerthree = 0; //Zero Byte
			ripheader->headerfour = 0; //Zero Byte
		} else {
			ripheader->headerone = command; //Command 
			ripheader->headertwo = version; //RIP Version
			ripheader->headerthree = 0; //Zero Byte
			ripheader->headerfour = 0; //Zero Byte
			
		}

		
		if (version == 2) {
			
			ripheader->byteone = 255; //Full Byte
			ripheader->bytetwo = 255; //Full Byte
			ripheader->bytefour = 0; //Auth Type
			ripheader->bytefive = authtype; //Auth Type
			
		} else {
			
			ripheader->byteone = 0;
			ripheader->bytetwo = addrfamily;
			ripheader->bytefour = 0;
			ripheader->bytefive = 0;
			
		}
		
		if (version == 2) {
			
			//Password
			ripheader->bytefive = passwordint[0];
			ripheader->bytesix = passwordint[1];
			ripheader->byteseven = passwordint[2];
			ripheader->byteeight = passwordint[3];
			ripheader->bytenine = passwordint[4];
			ripheader->byteten = passwordint[5];
			ripheader->byteeleven = passwordint[6];
			ripheader->bytetwelve = passwordint[7];
			ripheader->bytethirteen = passwordint[8];
			ripheader->bytefourteen = passwordint[9];
			ripheader->bytefifteen = passwordint[10];
			ripheader->bytesixteen = passwordint[11];
			ripheader->byteseventeen = passwordint[12];
			ripheader->byteeighteen = passwordint[13];
			ripheader->bytenineteen = passwordint[14];
			ripheader->bytetwenty = passwordint[15];
			
		} else {
			
			ripheader->bytefive = netip[0] ;
			ripheader->bytesix = netip[1] ;
			ripheader->byteseven = netip[2] ;
			ripheader->byteeight = netip[3] ;
			ripheader->bytenine = 0;
			ripheader->byteten = 0;
			ripheader->byteeleven = 0;
			ripheader->bytetwelve = 0;
			ripheader->bytethirteen = 0;
			ripheader->bytefourteen = 0;
			ripheader->bytefifteen = 0;
			ripheader->bytesixteen = 0;
			ripheader->byteseventeen = 0;
			ripheader->byteeighteen = 0;
			ripheader->bytenineteen = 0;
			
			ripheader->bytetwenty = metric[3];
			
		}
		
		if (version == 2) {
			
		//Address Family
		ripheader->bytetwentyone = 0;
		ripheader->bytetwentytwo = addrfamily; //The Address Family (IP)
		
		//Route Tag
		ripheader->bytetwentythree = 0;
		ripheader->bytetwentyfour = routetag; //The Route Tags Feild
		
		//IP Address
		ripheader->bytetwentyfive = netip[0] ; //First byte of the IP Address
		ripheader->bytetwentysix = netip[1] ; //Second byte of the IP Address
		ripheader->bytetwentyseven = netip[2] ; //Third byte of the IP Address
		ripheader->bytetwentyeight = netip[3] ; //Fourth byte of the IP Addresss
		
		//Subnet mask
		ripheader->bytetwentynine = subnetmask[0]; //First byte of the Subnet Mask
		ripheader->bytethirty = subnetmask[1]; //Second Byte of the Subnet Mask
		ripheader->bytethirtyone = subnetmask[2]; //Third byte of the Subnet Mask
		ripheader->bytethirtytwo = subnetmask[3]; //Fourth byte of the Subnet Mask
		
		//Next Hop 
		ripheader->bytethirtythree = nexthopip[0]; //First byte of the next hop
		ripheader->bytethirtyfour = nexthopip[1]; //Second byte of the next hop
		ripheader->bytethirtyfive = nexthopip[2]; //Third byte of the next hop
		ripheader->bytethirtysix = nexthopip[3]; //Fourth byte of the next hop
		
		//Metric
		ripheader->bytethirtyseven = metric[0]; //First Byte of the Metric
		ripheader->bytethirtyeight = metric[1]; //Second Byte of the Metric
		ripheader->bytethirtynine = metric[2]; //Third Byte of the Metric
		ripheader->byteforty = metric[3]; //Fourth Byte of the Metric
			
		}
			
		
		//Get the size of the struct
		size_t sizeofstruct = sizeof( struct ripdatagram );
	
		
		
		if ( verboseflag == 1 ) {
			//Print status saying we've generated the RIP Header
			printf( "\r\nRIP Header Generated Successfully\r\n" );
			
			//Render the packet to the stdout
			packet_renderer(headerbuf , dstipaddr );
			
		}
		
		//Create a socket
		if ( ( udpsock = socket( AF_INET, SOCK_DGRAM, 17 ) ) < 0 ) {
			
			if ( verboseflag == 1 ) {
				//print failed status
				printf( "Opening Socket FAILED :( !\r\n" );
			}
			return 0;
		}
		
		//Set Properties of the Socket in the sockaddr_in struct
		destaddr.sin_family = AF_INET;
		//Set the destination IP Address
		destaddr.sin_addr.s_addr = inet_addr( dstipaddr );
		//Set the destination port
		destaddr.sin_port = htons(protoport);
		
		if ( verboseflag == 1) {
			//Print a status message
			printf( "\r\nPreparing to send RIP Datagram\r\n" );		
		}
		
		//Send the Datagram
		if ( sendto( udpsock, headerbuf, sizeofstruct, 0, ( struct sockaddr * ) &destaddr, sizeof( destaddr ) ) < 0 ) {

			if ( verboseflag == 1 ) {
				//Print status message
				printf( "\r\nSending RIP Datagram FAILED :( !\r\n" );
			}
				
			//Return 0
			return 0;
		}

		if ( verboseflag == 1 ) {
			//Print a status Message
			printf( "\r\nRIP DataGram Successfully Dispatched!\r\n\r\n" );
		}
		
		//Return 1
		return 1;

	}
	
	//Return 0
	return 0;

}
