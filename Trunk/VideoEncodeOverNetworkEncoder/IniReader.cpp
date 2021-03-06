#include "StdAfx.h"
#include <stdio.h>

#define FILE_LINE_LENGTH	1024 * 65

void ConvertLineToParam( char *Line )
{
	if( Line[0] == '#' )
	{
//		printf("Read comment line : %s\n", Line );
		return;
	}
	char *ValueStart = strstr( Line, "=" );
	if( ValueStart != NULL && ValueStart != Line )
	{
		ValueStart++;
		char	StrValue[ FILE_LINE_LENGTH ];
		strcpy_s( StrValue, FILE_LINE_LENGTH, ValueStart );

		if( strstr( Line, "VideoCapturePCIP" ) )
			GlobalData.VideoNetworkIP = _strdup( StrValue );
		else if( strstr( Line, "VideoCapturePCPort" ) )
			GlobalData.VideoNetworkPort = _strdup( StrValue );
		else if( strstr( Line, "AudioCapturePCIP" ) )
			GlobalData.AudioNetworkIP = _strdup( StrValue );
		else if( strstr( Line, "AudioCapturePCPort" ) )
			GlobalData.AudioNetworkPort = _strdup( StrValue );
		else if( strstr( Line, "FPSLimit" ) )
			GlobalData.FPSLimit = atoi( StrValue );
//		else if( strstr( Line, "MaxNetworkPacketSize" ) )
//			GlobalData.MaxPacketSize = atoi( StrValue );
		else if( strstr( Line, "ShowStatistics" ) )
			GlobalData.ShowStatistics = atoi( StrValue );
		else if( strstr( Line, "ForcedAudioLatency" ) )
			GlobalData.ForcedAudioLatency = atoi( StrValue );
	}
}

int ReadLine( FILE *file, char *Store, int MaxLen )
{
	int StoreIndex = 0;
	Store[ 0 ] = 0;

	char ch = getc(file);
	if( ch == EOF )
		return 0;
    while( (ch != '\n') && (ch != '\r') && (ch != EOF) && StoreIndex < MaxLen ) 
	{
        Store[ StoreIndex ] = ch;
        StoreIndex++;
        ch = getc( file );
    }
    Store[ StoreIndex++ ] = '\0';
	return StoreIndex;
}

void LoadSettingsFromFile( char *FileName )
{
	FILE *inf;
	if( FileName != NULL )
		errno_t err = fopen_s( &inf, FileName, "rt" );
	else
		errno_t err = fopen_s( &inf, "Config.txt", "rt" );
	if( inf )
	{
		char buff[ FILE_LINE_LENGTH ];
		int ReadRet;

		//read while comments until EOF
		while( ReadRet = ReadLine( inf, buff, FILE_LINE_LENGTH ) )
			ConvertLineToParam( buff );

		fclose( inf );
	}
}