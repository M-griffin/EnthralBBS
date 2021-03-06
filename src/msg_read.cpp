/***************************************************************************
 *   Copyright (C) 2004-2017 by Michael Griffin                            *
 *   mrmisticismo@hotmail.com                                              *
 *                                                                         *
 *   Purpose:                                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

# include "struct.h"
# include "msgs.h"
# include "conio.h"
# include "users.h"
# include "menu_func.h"
# include "user_list.h"
# include "msg_fse.h"
# include "msg_read.h"

# include "mb_api.h"

# include "msg_title.h"
# include "msg_email.h"

# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include <algorithm>

# include <cstdio>
# include <ctime>
# include <cctype>
# include <cstring>
# include <cstdlib>
# include <unistd.h>


using namespace std;


/**
 * Message Reader INI Exists
 */
int msgread_ini::msg_exists()
{
    iTop = 0;
    iBot = 0;

    strcpy(sVIEW,"");
    strcpy(sPAGENUM,"");
    strcpy(sPAGETOTAL,"");
    strcpy(sMOREUP,"");
    strcpy(sMOREUP_CHAR,"");
    strcpy(sMOREDOWN,"");
    strcpy(sMOREDOWN_CHAR,"");
    strcpy(sMOREMSG_ON,"");
    strcpy(sMOREMSG_WORD_ON,"");
    strcpy(sMOREMSG_OFF,"");
    strcpy(sMOREMSG_WORD_OFF,"");

    strcpy(sTEXT_COLOR,"");
    strcpy(sQUOTE_COLOR,"");
    strcpy(sSYS_COLOR,"");
    strcpy(sORIGIN_COLOR,"");
    strcpy(sANSI_FILE,"");
    strcpy(sANSI_HELP,"");
    strcpy(sTHEME_NAME,"");
    strcpy(sMENU_PROMPT,"");
    strcpy(sMENU_PROMPT2,"");

    strcpy(sEOM_ON,"");
    strcpy(sEOM_WORD_ON,"");

    strcpy(sNXT_ON,"");
    strcpy(sNXT_WORD_ON,"");

    std::string path = INIPATH;
    path += "msgread.ini";

    FILE *stream;
    stream = fopen(path.c_str(),"rb+");
    if(stream == NULL) {
        perror("Error unable to read msgread.ini, check permissions!");
        return false;
    }
    fclose(stream);
    return true;
}

/**
 * Message Reader INI Create New File
 */
void msgread_ini::msg_create()
{
    std::string name = INIPATH;
    name += "msgread.ini";

    ofstream outStream2;
    outStream2.open( name.c_str(), ofstream::out | ofstream::trunc );
    if (!outStream2.is_open()) {
        printf( "\nError Creating: %s \n", name.c_str());
        return;
    }
    outStream2 << "# Default File Created by Program." << endl;
    outStream2.close();
    return;
}

/**
 * Message Reader INI Parse Value in Config
 */
void msgread_ini::msg_chkpar(std::string &data)
{
    std::string temp1;
    std::string::size_type st1 = 0;
    std::string::size_type st2 = 0;
    std::string::size_type  ct = 0;

    st1 = data.find('"', 0);
    st2 = data.find('"', st1+1);
    ++st1;
    temp1 = data.substr(st1,st2);
    ct = st2 - st1;
    if (temp1.length() > ct)
        temp1.erase(ct,temp1.length());
    data = temp1;
}

/**
 * Message Reader INI Check for Variables Settings
 */
void msgread_ini::msg_check(std::string cfgdata)
{
    std::string::size_type id1;
    std::string temp = cfgdata;
    if (temp[0] == '#') return;
    else if (temp.find("set VIEW_TYPE ", 0) !=
             std::string::npos) {
        msg_chkpar(temp);
        strcpy(sVIEW,(char *)temp.c_str());
    } else if (temp.find("set THEME_NAME ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sTHEME_NAME,(char *)temp.c_str());
    } else if (temp.find("set ANSI_FILE ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sANSI_FILE,(char *)temp.c_str());
    } else if (temp.find("set ANSI_HELP ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sANSI_HELP,(char *)temp.c_str());
    } else if (temp.find("set MENU_PROMPT ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sMENU_PROMPT,(char *)temp.c_str());
    } else if (temp.find("set MENU_PROMPT2 ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sMENU_PROMPT2,(char *)temp.c_str());
    } else if (temp.find("set TOP ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        id1 = atoi(temp.c_str());
        iTop = id1;
    } else if (temp.find("set BOT ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        id1 = atoi(temp.c_str());
        iBot = id1;
    } else if (temp.find("set PAGENUM ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sPAGENUM,(char *)temp.c_str());
    } else if (temp.find("set PAGETOTAL ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sPAGETOTAL,(char *)temp.c_str());
    } else if (temp.find("set MOREUP ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sMOREUP,(char *)temp.c_str());
    } else if (temp.find("set MOREUP_CHAR ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sMOREUP_CHAR,(char *)temp.c_str());
    } else if (temp.find("set MOREDOWN ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sMOREDOWN,(char *)temp.c_str());
    } else if (temp.find("set MOREDOWN_CHAR ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sMOREDOWN_CHAR,(char *)temp.c_str());
    } else if (temp.find("set MOREMSG_ON ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sMOREMSG_ON,(char *)temp.c_str());
    } else if (temp.find("set MOREMSG_WORD_ON ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sMOREMSG_WORD_ON,(char *)temp.c_str());
    } else if (temp.find("set EOM_ON ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sEOM_ON,(char *)temp.c_str());
    } else if (temp.find("set EOM_WORD_ON ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sEOM_WORD_ON,(char *)temp.c_str());
    } else if (temp.find("set NXT_ON ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sNXT_ON,(char *)temp.c_str());
    } else if (temp.find("set NXT_WORD_ON ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sNXT_WORD_ON,(char *)temp.c_str());
    } else if (temp.find("set MOREMSG_OFF ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sMOREMSG_OFF,(char *)temp.c_str());
    } else if (temp.find("set MOREMSG_WORD_OFF ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sMOREMSG_WORD_OFF,(char *)temp.c_str());
    } else if (temp.find("set TEXT_COLOR ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sTEXT_COLOR,(char *)temp.c_str());
    } else if (temp.find("set QUOTE_COLOR ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sQUOTE_COLOR,(char *)temp.c_str());
    } else if (temp.find("set SYS_COLOR ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sSYS_COLOR,(char *)temp.c_str());
    } else if (temp.find("set ORIGIN_COLOR ", 0) !=
               std::string::npos) {
        msg_chkpar(temp);
        strcpy(sORIGIN_COLOR,(char *)temp.c_str());
    }
}

/**
 * Message Reader Parse INI File
 */
int msgread_ini::msg_parse(int idx)
{
    if (!msg_exists())
        msg_create();

    char name[255]= {0};
    char name2[255]= {0};

    sprintf(name,"%smsgread.ini",INIPATH);
    sprintf(name2,"%smsgread%i.ini",INIPATH,idx);

    if (idx != 0) strcpy(name,name2);

    FILE *stream;
    stream = fopen(name,"rb+");
    if(stream == NULL) {
        return FALSE;
    }
    fclose(stream);

    ifstream inStream;
    inStream.open( name );
    if (!inStream.is_open()) {
        perror("Error unable to parse msgread.ini, check permissions!");
        return FALSE;
    }

    std::string cfgdata;
    for (;;) {
        std::getline(inStream,cfgdata,'\n');
        msg_check(cfgdata);
        if(inStream.eof()) break;
    }
    inStream.close();
    return TRUE;
}

/**
 * Message Reader Constructor
 */
msg_read::msg_read()
{
    tTop       = 1;
    tBot       = 1;
    Views      = 0;
    opscan     = FALSE;
    firstscan  = 0;
    gblNewScan = 0;
}

/**
 * Message Reader Start-Up Class
 */
void msg_read::start(UserRec *user)
{
    thisuser = user;
    start_session(user);

    if (msg_parse(thisuser->readertheme) == FALSE)
        msg_parse();

    tTop = iTop;
    tBot = iBot;
}

/**
 * Message Reader Set Default and Select Themes
 */
int msg_read::change_theme(int idx)
{
    if (msg_parse(idx) == FALSE)
        return FALSE;

    thisuser->readertheme = idx;

    UserRec usr;
    usr = *thisuser;
    users _usr;
    _usr.users_write(&usr,usr.idx);

    tTop = iTop;
    tBot = iBot;
    return TRUE;
}

/**
 * Message Reader Parse And Display Reader Ansi
 */
void msg_read::ansi_file(char *filename)
{
    std::string path = ANSIPATH;
    path += filename;
    path += ".ans";

    char MCI[3]      = {0};
    char sTemp[1024] = {0};
    int  space = 0, foundr = 0, foundl = 0;

    std::string buff;
    readinAnsi(filename, buff);

    // Calcuate how many messages total and left by current index.
    TotMsgs = msgidx_translation->size();
    CurMsgs = current_msgidx+1;
    MsgsLeft = TotMsgs - CurMsgs;

    int id1 = 0;
    do {
        id1 = buff.find("%", 0);
        if (id1 == -1) break;

        memset(&MCI,0,sizeof(MCI));
        space = 0;
        // Check if MCI Code is Justified then Process this.
        if (buff[id1+3] == '{') {
            // Left Justify
            MCI[0] = buff[id1+4];
            MCI[1] = buff[id1+5];
            space  = atoi(MCI);
            foundr = FALSE;
            foundl = TRUE;
        } else if (buff[id1+3] == '}') {
            // Right Justify
            MCI[0] = buff[id1+4];
            MCI[1] = buff[id1+5];
            space  = atoi(MCI);
            foundl = FALSE;
            foundr = TRUE;
        }
        // Now Get MCI Code
        MCI[0] = buff[id1+1];
        MCI[1] = buff[id1+2];

        memset(&sTemp,0,sizeof(sTemp));

        if (strcmp(MCI,"TI") == 0) {
            sprintf(sTemp,"%s", (char *)mHead.time);
        } else if (strcmp(MCI,"FM") == 0) {
            sprintf(sTemp,"%s", (char *)mHead.from);
        } else if (strcmp(MCI,"TO") == 0) {
            sprintf(sTemp,"%s", (char *)mHead.to);
        } else if (strcmp(MCI,"FL") == 0) {
            sprintf(sTemp,"%s", (char *)mHead.flags);
        } else if (strcmp(MCI,"MA") == 0) {
            sprintf(sTemp,"%s", (char *)mHead.area);
        } else if (strcmp(MCI,"SU") == 0) {
            sprintf(sTemp,"%s", (char *)mHead.subj);
        } else if (strcmp(MCI,"CM") == 0) {
            sprintf(sTemp,"%lu", CurMsgs);
        } else if (strcmp(MCI,"HM") == 0) {
            sprintf(sTemp,"%lu", TotMsgs);
        } else if (strcmp(MCI,"ML") == 0) {
            sprintf(sTemp,"%lu", MsgsLeft);
        } else if (strcmp(MCI,"TH") == 0) {
            sprintf(sTemp,"#%i. %s",thisuser->readertheme+1,sTHEME_NAME);
        }

        // MCI Translation .
        if (foundl == TRUE) {
            lspacing(sTemp,space);
        } else if (foundr == TRUE) {
            rspacing(sTemp,space);
        }

        //If we Parsed Justify, then Erase that MCI Code as well.
        (space != 0) ?
        buff.replace(id1,6,sTemp):
        buff.replace(id1,3,sTemp);
    } while (1);

    pipe2ansi((char *)buff.c_str());
}

/**
 * Message Reader - Main Readin Text Only to Buffer
 */
void msg_read::ReadInMsgOnly(ulong marea)
{ 
    if(!ReadMsgArea(marea)) {
        return;
    }
    
    MsgSetupTxt();
}

/**
 * Message Reader - Main Reader Function
 */
int msg_read::ReadMsg(ulong marea, int showit, int newmsg, int private_area)
{
    ulong lr = 0;

    if (current_msgidx >= msgidx_translation->size()) {
        return FALSE;
    }

    lr = GetLastRead(thisuser->idx);

    if(!ReadMsgArea(marea)) {
        return FALSE;
    }

    if (showit) {
        if (private_area == TRUE && strcmp((char *)thisuser->handle,(char *)MI.To) == 0) {
            MsgSetupTxt();
        } else if (private_area == TRUE && strcmp((char *)thisuser->handle,(char *)MI.To) != 0 && opscan == FALSE) {
            // Blank, don't populate header or message!
        } else if (private_area == FALSE) {
            // Normal Message Reader (No Email)
            MsgSetupTxt();
            ++Views;
        } else {
            // Normal Message Reader (No Email) / Or Sysop Email Read.
            MsgSetupTxt();
            if (opscan != TRUE) ++Views;
        }
    } else {
        // Title Scan
        SetupMsgHdr(); 
    }

    // Public NewScan - Working!
    if(newmsg && showit) {
        if (lr < msgidx_translation->size()) {
            if (thisuser->lastmsg >= msgidx_translation->at(lr)) {
                SetLastRead(thisuser->idx, current_msgidx+1);
            }
        }
    }

    return TRUE;
}

/**
 * Message Reader - NewScan Read/NewScan Public Areas
 */
int msg_read::NewScanMsgs(int newmsg, ulong marea)
{
    return (ReadMsg(marea, TRUE, newmsg));
}

/**
 * Message Reader - NewScan Public Areas
 */
int msg_read::ScanMessages(ulong marea)
{
    return (NewScanMsgs(TRUE, marea));
}

/**
 * Message Reader - Read Public Areas
 */
int msg_read::ReadMessages(ulong marea)
{
    return (NewScanMsgs(FALSE, marea));
}

/**
 * Message Reader - Jump to Specific Message in Reader
 */
void msg_read::JumpToMessage()
{
    std::string AnsiString = "";
    char choice[500]   = {0};
    char szReplace[10] = {0};

    std::string::size_type id1 =  0;

    _lang.lang_get(choice,25);
    AnsiString = choice;
    id1 = AnsiString.find("|HM",0);
    if (id1 != std::string::npos) {
        sprintf(szReplace,"%lu",TotMsgs);
        AnsiString.replace(id1,3,szReplace);
    }

    int len = strlen(szReplace)+1;
    strcpy(choice,AnsiString.c_str());
    inputfield(choice,len);
    pipe2ansi(choice);
    getline(choice,len);

    if ((id1 = atoi(choice)) > 0);
    --id1;

    // Move to new Message
    if ( (signed)id1 >= 0 && id1 < msgidx_translation->size() ) {
        thisuser->lastmsg = msgidx_translation->at( id1 );
        current_msgidx = id1;
    } else {
        pipe2ansi((char *)"|CR|CR|15Invalid: |07Message number.  Try again! |DE |DE");
    }
}

/**
 * Message Reader - Mark All Message As Read.
 */
void msg_read::IgnoreTheRest(ulong marea)
{
    ulong curr_msg = 0;
    curr_msg = msgidx_translation->size()-1;
    thisuser->lastmsg = msgidx_translation->at( msgidx_translation->size()-1 );
    current_msgidx = curr_msg;
    SetLastRead(thisuser->idx, curr_msg+1);
}

/**
 * Message Reader - Mark Current Message as Deleted.
 */
int msg_read::DelCurMsg(ulong mbnum, ulong msgnum)
{
    char text[1024]= {0};
    unsigned char ch;
    int lastReadIdx = 0;
    int currReadIdx = -1;

    _lang.lang_get(text,28);
    int len = 3;
    inputfield(text,len);
    pipe2ansi(text);
    ch = getkey(true);
    putkey(ch);

    if (toupper(ch) == 'Y') {
        if (mr.Pubpriv == PRIVATE) {
            // If Private let originating poster or receiver delete message.
            if ((strcmp((char *)thisuser->handle, mHead.from) == 0) ||
                (strcmp((char *)thisuser->handle, mHead.to) == 0) ||
                (isSysop == TRUE)) {
            } else if (isSysop == TRUE) {
            } else {
                memset(&text,0,sizeof(text));
                _lang.lang_get(text,21);
                pipe2ansi(text);
                return FALSE;
            }
        }
        // Add check if real name or handle used here!!
        else if (strcmp((char *)thisuser->handle, mHead.from) != 0) {
            memset(&text,0,sizeof(text));
            _lang.lang_get(text,21);
            pipe2ansi(text);
            return FALSE;
        }
    } else
        return FALSE;

    BOOL res;
    res = jamapi_purgemsg(&mr, msgnum);
    if (res) {
        return FALSE;
    }

    users _usr;
    int iTotal = _usr.idx_count();
    for (int j = msgidx_translation->size()-1; j >= 0; j--) {
        if (msgidx_translation->at(j) == msgnum)
            currReadIdx = j;
    }

    // Should never get here.
    if (currReadIdx == -1) {
        return FALSE;
    }

    // Currnet Message Deleted, so move to previous message.
    if (currReadIdx > 0)
        --currReadIdx;

    // Only reset current person for private areas.
    if (mr.Pubpriv == PRIVATE) {
        lastReadIdx = GetLastRead(thisuser->idx);

        if (lastReadIdx > (signed)msgidx_translation->size())
            lastReadIdx = msgidx_translation->size();

        if (lastReadIdx > currReadIdx+1) {
            // Don't allow Negative index's, Always start at 0
            if (lastReadIdx <= 0)
                lastReadIdx = 1;
            SetLastRead(thisuser->idx, lastReadIdx-1);
        }
    } else {
        // This is a Public Area, Global Message Number(s)
        // Here we loop all Users and fix their lastRead.
        for (int iCnt = 0; iCnt != iTotal; iCnt++) {
            lastReadIdx = GetLastRead(iCnt);

            if (lastReadIdx > (signed)msgidx_translation->size())
                lastReadIdx = msgidx_translation->size();

            if (lastReadIdx > currReadIdx+1) {
                if (lastReadIdx <= 0)
                    lastReadIdx = 1;
                SetLastRead(iCnt, lastReadIdx-1);
            }
        }
    }

    thisuser->lastmsg = msgidx_translation->at(currReadIdx);
    CURRENT_MSGTITLE = currReadIdx;

    return TRUE;
}

/**
 * Message Reader - Scan All Areas, Move to Next After when current is finished.
 */
int msg_read::NextAreaScan()
{
    int total;

    total = _msgf.msg_count();

    if((signed)thisuser->lastmbarea < (total-1)) {
        ++thisuser->lastmbarea;
        CURRENT_MAREA = thisuser->lastmbarea;
        firstscan = TRUE;
        return TRUE;
    }
    return FALSE;
}

/**
 * Message Reader - Check Username / Handle (Sending New/Private Message
 */
int msg_read::verify_username(char *text, char *name)
{
    UserRec u;
    UserIdx index;
    memset(&u,0,sizeof(UserRec));
    memset(&index,0,sizeof(UserIdx));

    ulong usernum;
    usernum = atoi(name);
    if (usernum != 0) {
        if (idx_read(&index,usernum-1)) {
            strcpy((char *)u.handle, (char *)index.handle);
            pipe2ansi(text);
            putline((char *)u.handle);
            return TRUE;
        } else {
            return FALSE;
        }
    } else if(idx_match(name)) {
        strcpy((char *)u.handle, name);
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * Message Reader - Read User Signature File
 */
int msg_read::read_usersig(std::string &sig)
{
    std::string data;
    char usersig[255]= {0};
    sprintf(usersig,"%s%ld.sig", USRSIG, (ulong)thisuser->idx);
    ifstream ins;

    ins.open( usersig );
    if (!ins.is_open()) {
        return FALSE;
    }

    sig.erase();
    for (;;) {
        std::getline(ins,data,'\r');
        if (ins.eof()) break;
        sig.append(data);
        if (ins.eof()) break;
        sig += '\r';
    }
    ins.close();

    buff = buff.substr(0,buff.size()-1 );
    return TRUE;
}

/**
 * Message Reader - Write User Signature
 */
void msg_read::write_usersig(std::string &tmp)
{
    char usersig[1024]= {0};
    sprintf(usersig,"%s%ld.sig",USRSIG, (ulong)thisuser->idx);

    if (tmp.size() == 0) {
        remove(usersig);
        return;
    }

    ofstream ostr;
    ostr.open( usersig, ofstream::out | ofstream::trunc );
    if (!ostr.is_open()) {
        return;
    }

    ostr << tmp;
    ostr.close();
}

/**
 * Message Reader - Add User Signature File Interface
 * If it already exists should read exiting into message editor.
 */
int msg_read::SetupUserSig()
{
    int  exists = FALSE, save=FALSE;
    std::string tmp;
    char text[1024]= {0};

    MsgHead     mHLocal;
    msg_readll  mLinkll;

    memset(&mHLocal,0,sizeof(MsgHead));

    // Check if Exists already in usersig folder.
    char usersig[1024]= {0};
    sprintf(usersig,"%s%ld.sig", USRSIG, (ulong)thisuser->idx);
    FILE *stream=fopen(usersig,"rb+");
    if(stream != NULL) {
        exists = TRUE;
        fclose(stream);
    }

    int ch = 0;

    // Prompt to Create/Edit, or Remove Existing.
    if (exists) {
        pipe2ansi ((char*)"|CS|CR |06Hit |14|18 ENTER |06|16 to Create/Edit, or |14|18 K |06|16 to Remove Current AutoSig|08: |07");
        int done = FALSE;
        while(!done) {
            ch = getkey(true);
            switch(toupper(ch)) {
            case 10 :
                done = TRUE;
                break;

            case 'K':
                remove(usersig);
                pipe2ansi ((char*)"|CS|CR |06|06AutoSig has been removed. |CR|PA");
                return TRUE;

            default :
                continue;
            }
        }
    }

    buff.erase();
    msg_fse _msge(thisuser);

    strcpy(mHLocal.to,"all");
    strcpy(mHLocal.from, (char *)thisuser->handle);

    if (exists)
        strcpy(mHLocal.subj,"Edit Your Message Auto Signature");
    if (!exists)
        strcpy(mHLocal.subj,"Create Your Message Auto Signature");

    strcpy(mHLocal.area,"Internal Editor");

    if (exists == TRUE) {
        if(read_usersig(tmp) == TRUE) {
            mLinkll.PutBufferSig((char *)tmp.c_str());
        } else
            return FALSE;

        save = _msge.poll_chr(FALSE, TRUE, &mHLocal, &mLinkll);

    } else {
        save = _msge.poll_chr(FALSE, FALSE, &mHLocal);
    }

    if (!save) {
        _lang.lang_get(text,35);
        pipe2ansi(text);
        return FALSE;
    }

    tmp.erase();
    tmp = _msge.buffer;

    write_usersig(tmp);

    _lang.lang_get(text,34);
    pipe2ansi(text);
    return TRUE;
}

/**
 * Message Reader - Get Netmail Address for sending private Netmails.
 */
void msg_read::get_address(XMSG *xm)
{
    char *zone,*net,*node,*pt;
    char faddr[21]= {0};
    char text[500]= {0};
    int len = 15;

    xm->dest.zone=0;
    xm->dest.net=0;
    xm->dest.node=0;
    xm->dest.point=0;

    *faddr='\0';
    inputfield(text,len);
    pipe2ansi((char *)"|CS|09Netmail |07- |15Insert Node Address below |11[|03xxx|15:|03xxx|15/|03xxx|11] |CR|08* ");
    pipe2ansi(text);
    getline(faddr,20);
    zone=strtok(faddr,":/.\n\r");

    if(zone) {
        xm->dest.zone=atoi(zone);
        net=strtok(NULL,":/.\n\r");
        if(net) {
            xm->dest.net=atoi(net);
            node=strtok(NULL,":/.\n\r");
            if(node) {
                xm->dest.node=atoi(node);
                pt=strtok(NULL,":/.\n\r");
                if(pt) {
                    xm->dest.point=atoi(pt);
                }
            }
        }
    }
}


/**
 * Message Reader - Post Private (Email/Netmail)
 */
void msg_read::DoPostEmail(int Reply)
{
    time_t timet;
    char rep[51]= {0}, text[500]= {0};
    char faddr[81]= {0};
    int  save, idx;
    std::string tmp;

    char to[21]   = {0};
    char from[21] = {0};
    char subj[61] = {0};

    UserIdx uidx;
    MsgHead mHLocal;

    msgs _msgf;
    _msgf.read_mbaselist(&mr, thisuser->lastmbarea);

    xmsg.orig.zone  = mr.aka.zone;
    xmsg.orig.net   = mr.aka.net;
    xmsg.orig.node  = mr.aka.node;
    xmsg.orig.point = mr.aka.point;

    time(&timet);
    xmsg.date_written = *timeTToStamp(timet);
    xmsg.date_arrived = *timeTToStamp(timet);

    xmsg.attr=0;
    xmsg.attr |= MSGLOCAL;

    if (Reply) {
        strcpy(to,mHead.from);
    } else {
        // Get To from User Listing.
        usr_list _ulist;
        _ulist.SetupEmailList(thisuser);
        idx = _ulist.StartList();

        memset(&uidx,0,sizeof(UserIdx));
        if (idx != EOF) idx_read(&uidx,idx);
        else {
            return;
        }
    }

    ansiPrintf((char *)"askemail");

    _lang.lang_get(text,47);
    int len = 20;
    inputfield(text,len);
    pipe2ansi(text);
    if (!Reply) {
        strcpy(to, (char *)uidx.handle);
    }
    
    pipe2ansi(to);

    // Get SUBJECT:
    _lang.lang_get(text,48);
    
    len = 60;
    inputfield(text,len);    
    pipe2ansi(text);
    
    // Mesasge Reply, Data Alreadt in mHead for Current Message.
    if (Reply) {
        strcpy(subj,mHead.subj);
        std::string sRe;
        if (subj != 0) {
            if (subj[0] != 'R' && subj[1] != 'e' && subj[2] != ':') {
                sRe = "Re: ";
                sRe += subj;
                strcpy(subj,(char *)sRe.c_str());
            }
            getline(subj,len,subj);
        } else getline(subj,len);
    } else {
        getline(subj,len);
    }

    // Blank Subject Return!
    if (strcmp(subj,"") == 0) {
        return;
    }
    buff.erase();

    // Get From:
    if ((mr.flags.mbrealname & 0x01) == 0)
        strcpy(from, (char *)thisuser->handle);
    else
        strcpy(from, (char *)thisuser->name);

    if(mr.Kind == NETMAIL) {
        get_address(&xmsg);
        xmsg.attr |= MSGPRIVATE;
        xmsg.attr |= MSGCRASH;
    }

    *rep = '\0';

    strcpy(mHLocal.to,to);
    strcpy(mHLocal.from,from);
    strcpy(mHLocal.subj,subj);
    strcpy(mHLocal.area,(const char *)mr.mbdisplay);

    // If were in reply, send current Message text to FSE for Quoting!
    msg_fse _msge(thisuser);
    if (Reply) {
        // Send Original Message for Quoter and FSE.
        save = _msge.poll_chr(Reply, FALSE, &mHLocal, &mLink);
    } else {
        // Start Fresh
        save = _msge.poll_chr(Reply, FALSE, &mHLocal);
    }
    if (!save) {
        _lang.lang_get(text,35);
        pipe2ansi(text);
        return;
    }

    buff = _msge.buffer;

    // Now append user signature. if exists
    if (read_usersig(tmp) == TRUE) {
        if (tmp.size() > 1) {
            buff += "\r\r";
            buff += tmp;
            buff += "\r";
        }
    }

    if (mr.Kind != LOCAL && mr.Kind != EMAIL) {
        if (mr.aka.point != 0) {
            sprintf(faddr," (%d:%d/%d.%d)",
                    mr.aka.zone, mr.aka.net, mr.aka.node, mr.aka.point);
        } else {
            sprintf(faddr," (%d:%d/%d) ",
                    mr.aka.zone, mr.aka.net, mr.aka.node);
        }
        buff += "\r--- ";
        buff += BBSVERSION;
        buff += " ";
        buff += OSSYSTEM;
        buff += "\r * Origin: ";
        buff += (char *)mr.origin_line;
        buff += faddr;
        buff += "\r";
    }

    strcpy((char*)xmsg.from, mHLocal.from);
    strcpy((char*)xmsg.to,   mHLocal.to);
    strcpy((char*)xmsg.subj, mHLocal.subj);

    SaveMsg(0,0,TRUE);

    memset(&text, 0, sizeof(100));

    _lang.lang_get(text,34);
    pipe2ansi(text);

    //hist_update(HIST_EMAILS,thisuser);
}

/**
 * Message Reader - Post Public Message
 */
void msg_read::DoPost(int mbnum, int Reply)
{
    time_t timet;
    char text[500]= {0};
    int  save;
    char faddr[81]= {0};
    std::string tmp;

    char to[21]   = {0};
    char from[21] = {0};
    char subj[61] = {0};

    MsgHead mHLocal;

    msgs _msgf;
    _msgf.read_mbaselist(&mr, mbnum);


    xmsg.orig.zone  = mr.aka.zone;
    xmsg.orig.net   = mr.aka.net;
    xmsg.orig.node  = mr.aka.node;
    xmsg.orig.point = mr.aka.point;

    time(&timet);
    xmsg.date_written = *timeTToStamp(timet);
    xmsg.date_arrived = *timeTToStamp(timet);

    xmsg.attr=0;
    xmsg.attr |= MSGLOCAL;

    // Change this to mr.type == sysop post only, not same as sysop area.
    // Test if Sysop Base, then only sysop may post!
    if (strcmp((char *)mr.mbfile,"system") == 0 ||
        strcmp((char *)mr.mbfile,"notice") == 0) {
        if (isSysop == FALSE) {
            pipe2ansi((char *)"|CR Sorry, only Sysop's may post to this area!");
            sleep(1);
            return;
        }
    }

    // Get From:
    if ((mr.flags.mbrealname & 0x01) == 0)
        strcpy(from, (char *)thisuser->handle);
    else
        strcpy(from, (char *)thisuser->name);

    if(mr.Kind == NETMAIL) {
        get_address(&xmsg);
        xmsg.attr |= MSGPRIVATE;
        xmsg.attr |= MSGCRASH;
    }

    // Get TO:
    _lang.lang_get(text,20);
    int len = 20;
    inputfield(text,len);
    pipe2ansi(text);

    if (Reply) {
        strcpy(to,mHead.from);
        getline(to,len,to);
    } else {
        strcpy(to,"all");
        getline(to,len,to);
    }

    // Get SUBJECT:
    _lang.lang_get(text,19);
    len = 60;
    inputfield(text,len);
    pipe2ansi(text);

    // Mesasge Reply, Data Alreadt in mHead for Current Message.
    if (Reply) {
        strcpy(subj,mHead.subj);
        // Add Re: to First Replies Only!
        std::string sRe;
        if (subj != 0) {
            if (subj[0] != 'R' && subj[1] != 'e' && subj[2] != ':') {
                sRe = "Re: ";
                sRe += subj;
                strcpy(subj,(char *)sRe.c_str());
            }
            getline(subj,len,subj);
        } else getline(subj,len);
    } else {
        getline(subj,len);
    }

    // Blank Subject Return!
    if (strcmp(subj,"") == 0) return;

    buff.erase();

    strcpy(mHLocal.to,to);
    strcpy(mHLocal.from,from);
    strcpy(mHLocal.subj,subj);
    strcpy(mHLocal.area,(const char *)mr.mbdisplay);

    // If were in reply, send current Message text to FSE for Quoting!
    msg_fse _msge(thisuser);

    if (Reply) {
        // Send Original Message to With Text Quoter to FSE.
        save = _msge.poll_chr(Reply, FALSE, &mHLocal, &mLink);
    } else {
        save = _msge.poll_chr(Reply, FALSE, &mHLocal);
    }

    if (!save || _msge.buffer.size() == 0) {
        _lang.lang_get(text,35);
        pipe2ansi(text);
        _msge.buffer.erase();
        buff.erase();
        return;
    }

    // Get the Buffer back from FSE on Completed Message.
    // Add Control Header for MSGID and REPLYID, this was missed in rewrite!!!
    buff = _msge.buffer;

    // Process Sig if exists.
    if (read_usersig(tmp) == TRUE) {
        if (tmp.size() > 1) {
            buff += "\r\r";
            buff += tmp;

            if (mr.Kind != LOCAL && mr.Kind != EMAIL)
            { }
            else
                buff += "\r";
        }
    }

    //Add System Tag && Origin Line
    if (mr.Kind != LOCAL && mr.Kind != EMAIL) {
        if (mr.aka.point != 0) {
            sprintf(faddr," (%d:%d/%d.%d)",
                    mr.aka.zone, mr.aka.net, mr.aka.node, mr.aka.point);
        } else {
            sprintf(faddr," (%d:%d/%d) ",
                    mr.aka.zone, mr.aka.net, mr.aka.node);
        }

        buff += "\r--- ";
        buff += BBSVERSION;
        buff += " ";
        buff += OSSYSTEM;
        buff += "\r * Origin: ";
        buff += (char *)mr.origin_line;
        buff += faddr;
        buff += "\r";
    }

    strcpy((char*)xmsg.from, mHLocal.from);
    strcpy((char*)xmsg.to,   mHLocal.to);
    strcpy((char*)xmsg.subj, mHLocal.subj);

    memset(&text,0,sizeof(text));
    SaveMsg(mbnum, MI.cur_msg+1, Reply);

    _lang.lang_get(text,34);
    pipe2ansi(text);

    // Write History.
    if (Reply) hist_update(HIST_REPLIES,thisuser);
    else hist_update(HIST_POSTS,thisuser);

    // Local Posts or Echomail
    if (mr.Kind != LOCAL && mr.Kind != EMAIL) {
        hist_update(HIST_POSTS,thisuser);
    } else
        hist_update(HIST_LOCAL,thisuser);
}

/**
 * Message Reader - Post Public Message (Helper Function)
 */
void msg_read::SetupMsgPost()
{
    DoPost(thisuser->lastmbarea,FALSE);
}

/**
 * Message Reader - Saves Edited Message, Deletes current and Posts New
 *                  After edits and changes have been made.
 */
void msg_read::DoEdit(int mbnum)
{
    time_t timet;
    char faddr[500]  = {0};
    char tag[500]    = {0};
    char origin[500] = {0};
    char text[500]   = {0};

    int  save        = FALSE;

    unsigned char ch;

    if(!ReadMsgArea(mbnum)) {
        return;
    }

    xmsg.orig.zone  = mr.aka.zone;
    xmsg.orig.net   = mr.aka.net;
    xmsg.orig.node  = mr.aka.node;
    xmsg.orig.point = mr.aka.point;

    time(&timet);
    xmsg.date_written = *timeTToStamp(timet);
    xmsg.date_arrived = *timeTToStamp(timet);

    xmsg.attr=0;
    xmsg.attr |= MSGLOCAL;

    if(mr.Kind == NETMAIL) {
        xmsg.attr |= MSGPRIVATE;
        xmsg.attr |= MSGCRASH;
    }

    strcpy((char*)xmsg.from, mHead.from);
    strcpy((char*)xmsg.to, mHead.to);
    strcpy((char*)xmsg.subj, mHead.subj);

    // Setup System Tag && Origin Line
    if (mr.Kind != LOCAL) {
        if (mr.aka.point != 0) {
            sprintf(faddr," (%d:%d/%d.%d)",
                    mr.aka.zone, mr.aka.net, mr.aka.node, mr.aka.point);
        } else {
            sprintf(faddr," (%d:%d/%d) ",
                    mr.aka.zone, mr.aka.net, mr.aka.node);
        }
        sprintf(tag,"--- %s %s",BBSVERSION,OSSYSTEM);
        sprintf(origin," * Origin: %s%s",mr.origin_line,faddr);
    }

    buff.erase();
    mLink.cleartags(tag,origin);
    mLink.line_total();
    msg_fse _msge(thisuser);

    if (!save) {
        _lang.lang_get(text,35);
        pipe2ansi(text);
        return;
    } else {
        // Ask Here to save Edited Changes!
        _lang.lang_get(text,33);
        int len = 3;
        inputfield(text,len);
        pipe2ansi(text);
        ch = getkey(true);
        putkey(ch);

        if (toupper(ch) != 'Y') {
            return;
        }
    }

    buff = _msge.buffer;
    buff += "\r";
    buff += tag;
    buff += "\r";
    buff += origin;

    _lang.lang_get(text,34);
    pipe2ansi(text);
    hist_update(HIST_EDITS,thisuser);
}

/**
 * Message Reader - Edit Current Message, Deletes current and Posts New
 *                  After edits and changes have been made.
 */
void msg_read::EditMessage()
{
    char text[500]= {0};
    unsigned char ch;

    _lang.lang_get(text,31);
    int len = 3;
    inputfield(text,len);
    pipe2ansi(text);
    ch = getkey(true);
    putkey(ch);

    if (toupper(ch) == 'Y') {
        if (strcmp((char *)thisuser->handle,mHead.from) > 0 &&
            strcmp((char *)thisuser->name,mHead.from) > 0) {
            memset(&text,0,sizeof(text));
            _lang.lang_get(text,32);
            pipe2ansi(text);
            return;
        }
    } else
        return;

    DoEdit(thisuser->lastmbarea);
}

/**
 * Message Reader - Title Scan Message Reader and NewScan
 *                  Handles both Public and Private Areas.
 */
long msg_read::title_scan(int newmsg, int multiscan, char *mString)
{
    unsigned long prevarea = thisuser->lastmbarea;

    long prevmsgcount = -1;
    unsigned long msgcount     = 0;  // Count of Messages
    unsigned long newmsgcount  = 0;  // Count New Messages
    unsigned long lastread     = 0;  // Users Last Read

    // Set class variable if were in a global newscan of all areas.
    gblNewScan = multiscan;

    int private_area = FALSE;
    int read_return  = 0;     // Hold Return Code from Reader / RET = TitleScan
    CURRENT_MSGTITLE = 0;     // Reset Message Title to Begining for start.

    std::stringstream iconvert(mString);   // In

    int i = 0;
    if (iconvert >> i)
    {
        if (!multiscan) {
            thisuser->lastmbarea = i;
            CURRENT_MAREA = thisuser->lastmbarea;
        }
    }
    iconvert.clear();
    iconvert.str("");

    std::string AnsiString;
    char outbuff[1024] = {0};
    char szReplace[20] = {0};
    std::string::size_type id1;

    msg_title *_tlist;
    unsigned long current_msg = 0;
    vector < unsigned long > elist;
    current_msg = 0;

    int first_titlescan = TRUE;
    int ret = 0;
    int ch  = 0;

    // If this is the first loop on an all area scan, set to first area
    if (multiscan && first_titlescan) {
        thisuser->lastmbarea = 0;
        CURRENT_MAREA = 0;
    }

    std::string        tmp1;
    ansiPrintf ((char *)"mscan");

    if (multiscan)
        pipe2ansi((char *)"|CR|09Starting Global Message NewScan ...|CR |DE");

    while(1) {
        memset(&mr,0,sizeof(mb_list_rec));
        _msgf.read_mbaselist(&mr, thisuser->lastmbarea);

        // Set if this is a Public/Private Message Area
        if (mr.Pubpriv == PRIVATE)
            private_area = TRUE;
        else
            private_area = FALSE;

        // If new get users last read for area
        if (newmsg) {
            lastread = GetLastRead(thisuser->idx);
        }

        msgcount = CountMsgs(thisuser->lastmbarea, thisuser);
        newmsgcount = CountNewMsgs(thisuser->lastmbarea, thisuser);

        if (first_titlescan || prevmsgcount < (signed)msgcount) {

            prevmsgcount = msgcount;
            if (elist.size() > 0)
                vector < unsigned long >() . swap(elist);

            current_msg = 0;
            AnsiString.erase();

            if (newmsg)
                AnsiString.append("|CR|15|M#|07. |03|MA |15- |09Scanning |13|NM |09new out of |11|HM |09messages.");
            else
                AnsiString.append("|CR|15|M#|07. |03|MA |15- |09Scanning |11|HM |09total messages.");

            // If we have more then 1 new message, then display loading.
            if (newmsg && newmsgcount > 0)
                AnsiString.append("|CR|CR|15Loading Messages... |031 Moment|15. |DE");

            // If we have more then 1 while reading, then display loading.
            if (!newmsg && msgcount > 0)
                AnsiString.append("|CR|CR|15Loading Messages... |031 Moment|15. |DE");

            sprintf(outbuff,"%lu", msgcount);
            ParseLocalMCI(AnsiString, "|HM", outbuff);
            sprintf(outbuff,"%lu", newmsgcount);
            ParseLocalMCI(AnsiString, "|NM", outbuff);
            pipe2ansi ((char *)AnsiString.c_str());

            // If no Message in area then check if multiscan
            // to Skip to Next Area or exit.
            if (msgcount == 0) {
                if (multiscan)
                { }
                else
                    pipe2ansi((char *)"|CR|CR|07Sorry: |15No messages found at this time.|CR|CR");

                if (multiscan) {
                    if (NextAreaScan() == FALSE) {

                        AnsiString.erase();
                        AnsiString.append("|CS|CR|15NewScan Completed |07... |DE |CR|PA");
                        pipe2ansi ((char *)AnsiString.c_str());

                        vector < unsigned long >() . swap(elist);
                        thisuser->lastmbarea = prevarea;
                        CURRENT_MAREA = thisuser->lastmbarea;
                        if (elist.size() > 0)
                            vector < unsigned long >() . swap(elist);
                        return 0;
                    }

                    first_titlescan = TRUE;
                    prevmsgcount = -1;
                    continue;
                }
                // Else were done.
                if (elist.size() > 0)
                    vector < unsigned long >() . swap(elist);
                pipe2ansi((char *)"|PA ");
                return FALSE;
            }

            // If new message scan, check if any new messages, if none
            // Check if multiscan to skip to next area.
            if (newmsg && newmsgcount == 0) {
                if (multiscan)
                { }
                else
                    pipe2ansi((char *)"|CR|CR|07Sorry: |15No New messages found at this time.|CR|CR");

                if (multiscan) {

                    if (NextAreaScan() == FALSE) {
                        AnsiString.erase();
                        AnsiString.append("|CR|CR|15NewScan Completed |07... |DE |CR|PA");
                        pipe2ansi ((char *)AnsiString.c_str());
                        vector < unsigned long >() . swap(elist);

                        // Before exiting system, go back to original area!
                        thisuser->lastmbarea = prevarea;
                        CURRENT_MAREA = thisuser->lastmbarea;
                        if (elist.size() > 0)
                            vector < unsigned long >() . swap(elist);
                        return 0;
                    }

                    first_titlescan = TRUE;
                    prevmsgcount = -1;
                    if (elist.size() > 0)
                        vector < unsigned long >() . swap(elist);
                    continue;
                } else {
                    if (elist.size() > 0)
                        vector < unsigned long >() . swap(elist);
                    pipe2ansi((char *)"|PA ");
                    return FALSE;
                }
            }

            if (elist.size() > 0)
                vector < unsigned long >() . swap(elist);

            if (private_area) {
                elist = jamapi_build_private(&mr, thisuser);
            } else {
                elist = jamapi_build_public(&mr, thisuser);
            }

            if ((newmsgcount > 0) || (msgcount > 0))
                pipe2ansi ((char *)"|CR|CR|15Loading Messages... |03Completed|15. |DE");

            // Setup Initial Starting Position in Title Scan
            // If NewScan start at Users LastRead Pointer.
            // Otherwise start at the first message in the array / list.
            if (first_titlescan) {
                first_titlescan = FALSE;
                if (newmsg) {
                    // Check if LastRead is past the end, means no new messages.
                    if (lastread < elist.size()) {
                        current_msg       = elist[lastread];
                        thisuser->lastmsg = current_msg;
                        CURRENT_MSGTITLE  = lastread;
                    } else {
                        if (multiscan)
                        { }
                        else
                            pipe2ansi((char *)"|CR|CR|07Sorry: |15No new messages found at this time.|CR|CR");

                        vector < unsigned long >() . swap(elist);
                        if (multiscan) {
                            if (NextAreaScan() == FALSE) {
                                AnsiString.erase();
                                AnsiString.append("|CR|CR|15NewScan Completed |07... |CR|PA");
                                pipe2ansi ((char *)AnsiString.c_str());
                                vector < unsigned long >() . swap(elist);
                                thisuser->lastmbarea = prevarea;
                                CURRENT_MAREA = thisuser->lastmbarea;
                                if (elist.size() > 0)
                                    vector < unsigned long >() . swap(elist);
                                return 0;
                            }
                            // Jump to next area

                            first_titlescan = TRUE;
                            prevmsgcount = -1;
                            if (elist.size() > 0)
                                vector < unsigned long >() . swap(elist);
                            continue;
                        } else {
                            if (elist.size() > 0)
                                vector < unsigned long >() . swap(elist);
                            pipe2ansi((char *)"|PA ");
                            return 0;
                        }
                    }
                } else {
                    current_msg = elist[0];
                    thisuser->lastmsg = current_msg;
                    CURRENT_MSGTITLE = 0;
                }
            }
        }

        // Setup Message Title Scan Class, for Selecting Message to Read/Scan
        _tlist = new msg_title;
        _tlist->SetupList(thisuser, private_area); // Reset Thisuser in title clas
        ret = _tlist->StartTitleList(newmsg, thisuser->lastmbarea, elist, CURRENT_MSGTITLE);
        CURRENT_MSGTITLE = _tlist->CURRENT_BAR;
        delete _tlist;

        // Done Scanning Exit!
        if (ret == EOF) {
            if (multiscan) {
                ansiPrintf ((char *)"mscan");
                pipe2ansi((char *)"|CR|09Global Message NewScan|CR|CR|15|M#|07. |03|MA |15- |09Scanning Exited.");
                pipe2ansi((char *)"|CR|CR|15Use: |CR|15[|11ENTER|15] |07Continue to Next Area, or |15[|11Q|15] |07to Quit Global NewScan|08: |07");
                while (1) {
                    ch = getkey(true);

                    if ((int)ch == 10) { // ENTER
                        if (NextAreaScan() == FALSE) {
                            AnsiString.erase();
                            AnsiString.append("|CR|CR|15NewScan Completed |07... |DE |CR|PA");
                            pipe2ansi ((char *)AnsiString.c_str());
                            vector < unsigned long >() . swap(elist);
                            thisuser->lastmbarea = prevarea;
                            CURRENT_MAREA = thisuser->lastmbarea;
                            if (elist.size() > 0)
                                vector < unsigned long >() . swap(elist);
                            return 0;
                        }

                        first_titlescan = TRUE;
                        prevmsgcount = -1;
                        if (elist.size() > 0)
                            vector < unsigned long >() . swap(elist);
                        break;
                    }
                    // If Q, Then exit Scan and return to menu.
                    else if (toupper(ch) == 'Q') {
                        // Done with NewScan Exit.
                        AnsiString.erase();
                        AnsiString.append("|CR|CR|15Exiting Title Scan |07... |DE");
                        pipe2ansi ((char *)AnsiString.c_str());

                        if (elist.size() > 0)
                            vector < unsigned long >() . swap(elist);
                        return 0;
                    }
                }

                // if ENTER was hit in while loop, start over for next area scan
                if ((int)ch == 10) { // ENTER
                    ch = 0;
                    continue;
                }
            }

            // Normal Exit on NewScan or Reading.
            AnsiString.erase();
            AnsiString.append("|CR|CR|15Exiting Title Scan |07... |DE");
            pipe2ansi ((char *)AnsiString.c_str());

            if (elist.size() > 0)
                vector < unsigned long >() . swap(elist);
            return 0;
        }
        // Continue to next area in newscan
        else if(ret == -2 && multiscan) {

            pipe2ansi((char *)"|CR|CR|15Skipping to Next Area |07... |DE");
            // Received Jump to Next Area
            if (NextAreaScan() == FALSE) {

                // No area's left in scan, so exit.
                AnsiString.erase();
                AnsiString.append("|CS|CR|15NewScan Completed |07... |CR|PA");
                pipe2ansi ((char *)AnsiString.c_str());

                vector < unsigned long >() . swap(elist);
                thisuser->lastmbarea = prevarea;
                CURRENT_MAREA = thisuser->lastmbarea;
                if (elist.size() > 0)
                    vector < unsigned long >() . swap(elist);
                return 0;
            }
            // Jump to next area

            first_titlescan = TRUE;
            prevmsgcount = -1;
            if (elist.size() > 0)
                vector < unsigned long >() . swap(elist);
            continue;
        }

        // Handle Passthrough options from Title Scan.
        // Negative numbers are exit and next area and passthrough codes.
        if (ret != -3) {
            // Translate Current Message for Functions
            thisuser->lastmsg = elist[CURRENT_MSGTITLE];
            switch (ret) {
                // Global NewScan Only.
            case 'B': // Bypass -  Leave Message Unread, skip to next area
                if (newmsg) {
                    current_msg = 0;
                    current_msg = elist.size()-1;
                    thisuser->lastmsg = elist.at( elist.size()-1 );
                    CURRENT_MSGTITLE = current_msg;
                    pipe2ansi((char *)"|CR|CR|07FYI: |15Remaining messages bypassed, left as |03unread|15.|CR|CR|PA");
                    // If global newscan skip to next area now.
                    if (multiscan) {
                        pipe2ansi((char *)"|CR|CR|15Skipping to Next Area |07... |DE");
                        // Received Jump to Next Area
                        if (NextAreaScan() == FALSE) {
                            AnsiString.erase();
                            AnsiString.append("|CR|CR|15NewScan Completed |07... |CR|PA");
                            pipe2ansi ((char *)AnsiString.c_str());
                            vector < unsigned long >() . swap(elist);

                            // Before exiting system, go back to original area!
                            thisuser->lastmbarea = prevarea;
                            CURRENT_MAREA = thisuser->lastmbarea;
                            if (elist.size() > 0)
                                vector < unsigned long >() . swap(elist);
                            return 0;
                        }
                        // Jump to next area

                        first_titlescan = TRUE;
                        prevmsgcount = -1;
                        if (elist.size() > 0)
                            vector < unsigned long >() . swap(elist);
                        continue;
                    }
                    continue;
                }
                continue;

            case 'I': // Ignore -  Mark Remaining as Read
                current_msg = 0;

                current_msg = elist.size()-1;
                thisuser->lastmsg = elist.at( elist.size()-1 );
                CURRENT_MSGTITLE = current_msg;
                SetLastRead(thisuser->idx, current_msg+1);

                pipe2ansi((char *)"|CR|CR|07FYI: |15Remaining messages ignored, marked as |03read|15.|CR|CR|PA");

                first_titlescan = TRUE;
                prevmsgcount = -1;

                // If global newscan skip to next area now.
                if (multiscan) {
                    pipe2ansi((char *)"|CR|CR|15Jumping to Next Area |07... |DE");
                    // Received Jump to Next Area
                    if (NextAreaScan() == FALSE) {
                        AnsiString.erase();
                        AnsiString.append("|CR|CR|15NewScan Completed |07... |CR|PA");
                        pipe2ansi ((char *)AnsiString.c_str());
                        vector < unsigned long >() . swap(elist);
                        
                        // Before exiting system, go back to original area!
                        thisuser->lastmbarea = prevarea;
                        CURRENT_MAREA = thisuser->lastmbarea;
                        if (elist.size() > 0)
                            vector < unsigned long >() . swap(elist);
                        return 0;
                    }
                    // Jump to next area

                    first_titlescan = TRUE;
                    prevmsgcount = -1;
                    if (elist.size() > 0)
                        vector < unsigned long >() . swap(elist);
                    continue;
                }
                continue;


            case 'K': // Kill / Delete Message
                // Readin, then Test if User has Access to Remove Message.
                ReadInMsgOnly(CURRENT_MAREA);

                // Build Index to Pass for Delete Function
                msgidx_translation = new vector<ulong>;
                for (int j = 0; j < (signed)elist.size(); j++) {
                    msgidx_translation->push_back(elist.at(j));
                }


                if(DelCurMsg(thisuser->lastmbarea, thisuser->lastmsg)) {
                    pipe2ansi((char *)"|CR|CR|07FYI: |15Current Message has been deleted.|CR|CR|PA");
                    prevmsgcount = -1;
                    if (elist.size() > 0)
                        vector < unsigned long >() . swap(elist);
                }

                delete msgidx_translation;
                mLink.Lines = 0;
                mLink.dispose();
                continue;

            case 'E': // Edit Message
                pipe2ansi((char *)"|CR|CR|07FYI: |15WIP - Not yet Implimented.|CR|CR|PA");
                continue;

            case 'H': // Set Pointer
                memset(&outbuff,0,sizeof(outbuff));
                SetLastRead(thisuser->idx, CURRENT_MSGTITLE+1);

                _lang.lang_get(outbuff,37);
                AnsiString = outbuff;
                id1 = AnsiString.find("|M#",0);
                if (id1 != std::string::npos) {
                    sprintf(szReplace,"%d", CURRENT_MSGTITLE+1);
                    AnsiString.replace(id1,3,szReplace);
                }
                pipe2ansi((char*)AnsiString.c_str());
                continue;

            case 'P': // Post a New Message
                if (mr.Pubpriv == PRIVATE) {
                    DoPostEmail(FALSE);
                } else {
                    DoPost(CURRENT_MAREA, FALSE);
                }

                pipe2ansi((char *)"|CS");
                prevmsgcount = -1;
                if (elist.size() > 0)
                    vector < unsigned long >() . swap(elist);

                mLink.Lines = 0;
                mLink.dispose();
                continue;

            case 'R': // Reply to a Message
                ReadInMsgOnly(CURRENT_MAREA);

                if (mr.Pubpriv == PRIVATE) {
                    DoPostEmail(TRUE);
                } else {
                    DoPost(CURRENT_MAREA, TRUE);
                }

                pipe2ansi((char *)"|CS");
                prevmsgcount = -1;
                if (elist.size() > 0)
                    vector < unsigned long >() . swap(elist);

                mLink.Lines = 0;
                mLink.dispose();
                continue;

            default:
                continue;
            }
        }

        // Then we have area from title scan
        if (ret == -3)
            ret = CURRENT_MSGTITLE;
        else continue;

        current_msg = elist[ret];

        // After reading current message, jump to next message.
        thisuser->lastmsg = current_msg;

        // Make Copy of elist into Private list
        // For Use in Class for Reader!
        msgidx_translation = new vector<ulong>;
        for (int j = 0; j < (signed)elist.size(); j++) {
            msgidx_translation->push_back(elist.at(j));
        }

        read_return = StartReader(newmsg, ret);


        // Now Check Return Code From Reader, for Global NewScans,
        // If end of message, bypass, ignore,  we get -2 for skip to next area
        // in the NewScan.  Otherwise passthrough.

        // Continue to next area in newscan
        if(read_return == -2 && multiscan) {
            pipe2ansi((char *)"|CS|CR|15Jumping to Next Area |07... |DE");
            // Received Jump to Next Area
            if (NextAreaScan() == FALSE) {
                AnsiString.erase();
                AnsiString.append("|CS|CR|15NewScan Completed |07... |CR|PA");
                pipe2ansi ((char *)AnsiString.c_str());
                vector < unsigned long >() . swap(elist);

                // Before exiting system, go back to original area!
                thisuser->lastmbarea = prevarea;
                CURRENT_MAREA = thisuser->lastmbarea;
                if (elist.size() > 0)
                    vector < unsigned long >() . swap(elist);
                return 0;
            }
            // Jump to next area

            first_titlescan = TRUE;
            prevmsgcount = -1;
            if (elist.size() > 0)
                vector < unsigned long >() . swap(elist);
            continue;
        }

        // Deleted a message, fresh and drop back to Title Scan`
        if(read_return == -3) {
            prevmsgcount = -1;
            delete msgidx_translation;
            if (elist.size() > 0) 
                vector < unsigned long >() . swap(elist);
            continue;
        }       
        else {            
            delete msgidx_translation;

            AnsiString.erase();
            AnsiString.append("|CS|CR|15Returning to Title Scan |07... ");
            pipe2ansi ((char *)AnsiString.c_str());

            continue;
        }

        // Make sure Message isn't past the end of translation array
        if (CURRENT_MSGTITLE+1 >= (signed)elist.size()) {
            CURRENT_MSGTITLE = elist.size()-2;
            current_msg = elist[elist.size()-2]; // Gets incrimented, set to last!
        } else {
            current_msg = elist[CURRENT_MSGTITLE+1];
        }

        // After reading current message, jump to next message.
        thisuser->lastmsg = current_msg;

        // Move to Next Lightbar in Title Scan.
        CURRENT_MSGTITLE++;

        AnsiString.erase();
        AnsiString.append("|CS|CR|15Returning to Title Scan |07... ");
        pipe2ansi ((char *)AnsiString.c_str());

    } // End While

    thisuser->lastmbarea = prevarea;
    CURRENT_MAREA = prevarea;
    if (elist.size() > 0) //&& prevmsgcount == -1)
        vector < unsigned long >() . swap(elist); // Clear Vector.
    return 0;
}


/**
 * Message Reader -
 * - Handles both Public and Private Message Areas via Translation Index
 * - Translation Index is a vector index of all messages pre-populated.
 * - So all internal message counts stay true in order 1..2..3..4
 */
int msg_read::StartReader(int newmsg, ulong msgidx)
{
    std::string AnsiString;
    char        mString[1024]   = {0};
    char        szReplace[500]  = {0};
    char        text[1024]      = {0};

    int         rtnval          = TRUE;
    int         done            = FALSE;
    int         same            = FALSE;
    int         firstread       = TRUE;
    int         more            = FALSE;
    int         showmore        = FALSE;

    int             id1;
    int             cont;
    unsigned char   ch;

    std::string     _output;
    char            outBuffer[1024]= {0};

    menu_func       _mnuf;
    msgs            _msgf;

    int             idx;
    int             aCoordX;
    int             bCoordX;

    // Startup Message Reader Link List for Holding Message Lines
    mLink.initReader(sTEXT_COLOR, sQUOTE_COLOR, sSYS_COLOR, sORIGIN_COLOR);
    mLink.Top = tTop;
    mLink.Bot = tBot;

    current_msgidx = msgidx;
    opscan = FALSE;
    Views = 0;

    if(!ReadMsgArea(thisuser->lastmbarea)) {
        MI.high_msg   = 0;
        MI.high_water = 0;
        MI.active     = 0;
    }

    sprintf(szReplace,"%lu",MI.high_msg);
    memset(&mHead,0, sizeof(MsgHead));

    // Check if were doing a New Scan, or user is selecting starting #
    if (newmsg == TRUE) {
        firstscan = TRUE;
        _lang.lang_get(text,23);
        AnsiString = text;
        pipe2ansi((char*)AnsiString.c_str());

        // No Messages Found in this Area.
        if (msgidx_translation->size() < 1) {
            memset(&text,0,sizeof(text));
            _lang.lang_get(text,36);
            AnsiString = text;
            pipe2ansi((char*)AnsiString.c_str());
        }
    }
   
    // Run through Main Reader Loop until exit from user
    while (done == FALSE) {
        memset(&mHead,0, sizeof(MsgHead));
        same = TRUE;

        memset(&szReplace,0,sizeof(szReplace));
        memset(&text,0,sizeof(text));
        AnsiString.erase();

        if (newmsg == TRUE) {
            cont = ScanMessages(thisuser->lastmbarea);
        } else {
            cont = ReadMessages(thisuser->lastmbarea);
        }

        // Done in Current Area, Flip to Next Area in Scan or Exit.
        // NOTE Next ARea done in title scan!
        if (cont == FALSE ||
            thisuser->lastmsg > MI.high_msg ||
            current_msgidx >= msgidx_translation->size() ) {
            _msgf.read_mbaselist(&mr, thisuser->lastmbarea);
            _lang.lang_get(text,36);
            AnsiString = text;
            pipe2ansi((char*)AnsiString.c_str());

            mLink.Lines = 0;
            mLink.dispose_list();
            same = FALSE;
            done = TRUE;
            break;
        }

        if (firstread == TRUE) {
            firstread = FALSE;
            pipe2ansi((char *)"|CS");
        }

        // Here is the Full Screen Reader
        if (sVIEW[0] != 'S') {
            ansi_file(sANSI_FILE);
            mLink.box_start(thisuser->lastmbarea);
        } else {
            ansi_file(sANSI_FILE);
            aCoordX = iTop;
            bCoordX = 24;

            pipe2ansi((char *)"|CR");

            mLink.headerrows = aCoordX - bCoordX;
            ++mLink.headerrows;
            mLink.box_scroll_reader();
        }

        // Now loop Though and Parse Extras then Start Menu Input System.
        while(done == FALSE && same == TRUE) {
            _output.erase();
            more = FALSE;
            showmore = FALSE;
            mLink.Top = tTop;
            mLink.Bot = tBot;

            /// full screen message reader
            if (sVIEW[0] != 'S') {
                more = FALSE;
                showmore = FALSE;
                sprintf(outBuffer,"%s%s",sMOREMSG_OFF,sMOREMSG_WORD_OFF);
                pipe2ansi(outBuffer);

                if (mLink.Page < mLink.TotPages) more = TRUE;
                if (mLink.Page == mLink.TotPages && mLink.Page != 1) {
                    // Were on the Very Last Page of the Message
                    sprintf(outBuffer,"%s%s",sMOREMSG_OFF,sMOREMSG_WORD_OFF);
                    _output += outBuffer;

                    // Disaply End of Message Instead of Showing Up Arrow!
                    sprintf(outBuffer,"%s%s",sEOM_ON,sEOM_WORD_ON);
                    _output += outBuffer;
                }
                // Normal Process Checking  if there is a page above or below for MORE!
                else {
                    // Show Down Arrow More!
                    if (more) {
                        sprintf(outBuffer,"%s\x19",sMOREDOWN);
                        showmore = TRUE;
                    } else {
                        sprintf(outBuffer,"%s ",sMOREDOWN);
                    }
                    _output += outBuffer;

                    // Show up Arrow More
                    if (mLink.Page > 1) {
                        sprintf(outBuffer,"%s\x18",sMOREUP);
                        showmore = TRUE;
                    } else {
                        sprintf(outBuffer,"%s ",sMOREUP);
                    }
                    _output += outBuffer;

                    if (showmore)
                        sprintf(outBuffer,"%s%s",sMOREMSG_ON,sMOREMSG_WORD_ON);
                    else {
                        // Next Message
                        // Were on the Only Page
                        sprintf(outBuffer,"%s%s",sMOREMSG_OFF,sMOREMSG_WORD_OFF);
                        _output += outBuffer;

                        // Disaply Next / End of Message
                        sprintf(outBuffer,"%s%s",sNXT_ON,sNXT_WORD_ON);
                        _output += outBuffer;
                    }
                    _output += outBuffer;
                }

                // Show Current/Total Pages Per Message!
                // Usually noit going over 99 pages,, so 2d here is good.
                sprintf(outBuffer,"%s%.2d",sPAGENUM,mLink.Page);
                _output += outBuffer;
                sprintf(outBuffer,"%s%.2d",sPAGETOTAL,mLink.TotPages);
                _output += outBuffer;
                pipe2ansi((char *)_output.c_str());

                // Make Msgp2 Prompt Optional, Use if exists!
                // Also Let user Toggle on / off
                if (_mnuf.cmdexist(sMENU_PROMPT2,0)) {
                    if (more) {
                        _mnuf._curmenu.clear();
                        _mnuf._curmenu = sMENU_PROMPT2;
                    } else {
                        _mnuf._curmenu.clear();
                        _mnuf._curmenu = sMENU_PROMPT;
                    }
                } else {
                    _mnuf._curmenu.clear();
                    _mnuf._curmenu = sMENU_PROMPT;
                }

            } else {
                _mnuf._premenu.clear();
                _mnuf._curmenu.clear();
                _mnuf._curmenu = sMENU_PROMPT;

                _mnuf.TotMsgs = msgidx_translation->size();
                _mnuf.CurMsgs = current_msgidx+1;
                _mnuf.MsgsLeft = _mnuf.TotMsgs - _mnuf.CurMsgs;
            }

            _mnuf.menu_readin();
            _mnuf.menu_proc(mString);

            ch = mString[1];

            // For Menu CmdKey Input
            if (mString[0] == '!') {
                switch (toupper(ch)) {
                case '+': // Next Message
                    if (current_msgidx+1 < msgidx_translation->size()) {
                        current_msgidx +=1;
                        CURRENT_MSGTITLE +=1;
                        thisuser->lastmsg = msgidx_translation->at(current_msgidx);
                        mLink.Lines = 0;
                        mLink.dispose();
                        same = FALSE;
                        break;
                    } else {
                        current_msgidx = msgidx_translation->size()-1;
                        thisuser->lastmsg = msgidx_translation->at(current_msgidx);
                        CURRENT_MSGTITLE = current_msgidx;
                        pipe2ansi((char *)"|CS|CR|07FYI: |15You're at the highest message available.|CR|CR");

                        // If were in a newscan, check if we want to continue scan
                        // or return to titlescan
                        if (newmsg && gblNewScan) {
                            ansiPrintf ((char *)"mcont");

                            // Done with NewScan, Mark Messages As Read
                            // Then either goto next are or back to title scan.
                            while(1) {
                                ch = getkey(true);

                                if (ch == 10) {
                                    pipe2ansi((char *)" |CS ");
                                    IgnoreTheRest(thisuser->lastmbarea);
                                    mLink.Lines = 0;
                                    mLink.dispose();
                                    same = FALSE;
                                    done = TRUE;
                                    _mnuf.choice = 0;
                                    rtnval = -2;
                                    break;
                                } else if (toupper(ch) == 'Q') {
                                    pipe2ansi((char *)" |CS ");
                                    IgnoreTheRest(thisuser->lastmbarea);
                                    mLink.Lines = 0;
                                    mLink.dispose();
                                    same = FALSE;
                                    done = TRUE;
                                    break;
                                }
                            }
                        } else {
                            pipe2ansi((char *)"|PA |CS ");
                            mLink.Lines = 0;
                            mLink.dispose();
                            same = FALSE;
                            break;
                        }

                    }
                    break;

                case '-': // Previous Message
                    mLink.Lines = 0;
                    if (current_msgidx > 0) {
                        current_msgidx -= 1;
                        CURRENT_MSGTITLE -= 1;
                        thisuser->lastmsg = msgidx_translation->at(current_msgidx);
                    } else {
                        current_msgidx =0;
                        CURRENT_MSGTITLE = 0;
                        thisuser->lastmsg = msgidx_translation->at(current_msgidx);
                        pipe2ansi((char *)"|CS|CR|07FYI: |15You're at the lowest message available.|CR|CR|PA");
                        pipe2ansi((char *)" |CS ");
                    }
                    mLink.dispose();
                    same = FALSE;
                    break;

                case 'Q': // Quit Message Reading
                    rtnval = FALSE;
                    done = TRUE;
                    mLink.Lines = 0;
                    mLink.dispose_list();
                    same = FALSE;

                    if (newmsg) {
                        _msgf.read_mbaselist(&mr, thisuser->lastmbarea);
                        _lang.lang_get(text,36);
                        AnsiString = text;
                        pipe2ansi((char*)AnsiString.c_str());
                    }
                    break;

                case 'U': // Page UP
                    mLink.box_pgup();
                    break;

                case 'D': // Page Down
                    mLink.box_pgdn();
                    break;

                case 'P': // Post a New Message
                    if (mr.Pubpriv == PRIVATE) {
                        DoPostEmail(FALSE);
                    } else {
                        DoPost(CURRENT_MAREA, FALSE);
                    }

                    mLink.Lines = 0;
                    
                    std::cout << "dispose" << std::endl;
                    
                    mLink.dispose();
                    
                    std::cout << "dispose done" << std::endl;
                    
                    same = FALSE; // Refresh Message
                    pipe2ansi((char *)"|CS");
                    _mnuf.choice = 0;
                    rtnval = FALSE;
                    done = TRUE;

                    break;

                case 'R': // Reply to a Message
                    if (mr.Pubpriv == PRIVATE) {
                        DoPostEmail(TRUE);
                    } else {
                        DoPost(CURRENT_MAREA, TRUE);
                    }
                    mLink.Lines = 0;
                    mLink.dispose();
                    same = FALSE; // Refresh Message
                    pipe2ansi((char *)"|CS");
                    _mnuf.choice = 0;
                    rtnval = FALSE;
                    done = TRUE;
                    break;

                case 'H': // Set Last Read Pointer
                    memset(&text,0,sizeof(text));
                    SetLastRead(thisuser->idx, current_msgidx+1);

                    _lang.lang_get(text,37);
                    AnsiString = text;
                    id1 = AnsiString.find("|M#",0);
                    if (id1 != -1) {
                        sprintf(szReplace,"%ld", current_msgidx+1);
                        AnsiString.replace(id1,3,szReplace);
                    }
                    pipe2ansi((char*)AnsiString.c_str());

                    mLink.Lines = 0;
                    mLink.dispose();
                    same = FALSE;
                    pipe2ansi((char *)"|CS");
                    _mnuf.choice = 0;
                    break;

                case 'J': // Jump to Message #
                    JumpToMessage();
                    mLink.Lines = 0;
                    mLink.dispose();
                    same = FALSE;
                    pipe2ansi((char *)"|CS");
                    _mnuf.choice = 0;
                    break;

                case 'I': // Ignore
                    IgnoreTheRest(thisuser->lastmbarea);
                    mLink.Lines = 0;
                    mLink.dispose();
                    same = FALSE;
                    done = TRUE;

                    pipe2ansi((char *)"|CS|CR|07FYI: |15Remaining messages ignored, marked as read.|CR|CR|PA");
                    _mnuf.choice = 0;

                    // Pushes to Next Area in Global NewScan
                    if (newmsg && gblNewScan)
                        rtnval = -2;
                    break;

                case 'B': // Bypass The Rest (Doesn't Mark
                    // Set to Last Message, This doesn't set Previous did message +1
                    // Might need to fix or test this lateron,
                    current_msgidx = msgidx_translation->size()-1;
                    thisuser->lastmsg = msgidx_translation->at(current_msgidx);

                    mLink.Lines = 0;
                    mLink.dispose();
                    same = FALSE;
                    done = TRUE;
                    _mnuf.choice = 0;
                    pipe2ansi((char *)"|CS|CR|07FYI: |15Remaining messages bypassed, not marked as read.|CR|CR|PA");

                    // Pushes to Next Area in Global NewScan
                    if (newmsg && gblNewScan)
                        rtnval = -2;
                    break;
                    
                case 'K': // Kill Current Message
                    if (DelCurMsg(thisuser->lastmbarea, thisuser->lastmsg)) {
                        pipe2ansi((char *)"|CS|CR|07FYI: |15Current Message has been deleted.|CR|CR|PA");
                        mLink.Lines = 0;
                        mLink.dispose();
                        same = FALSE;
                        done = TRUE;
                        pipe2ansi((char *)"|CS");
                        _mnuf.choice = 0;
                        rtnval = -3;
                        break;
                    }

                    mLink.Lines = 0;
                    mLink.dispose();
                    same = FALSE;
                    done = TRUE;
                    pipe2ansi((char *)"|CS");
                    _mnuf.choice = 0;
                    break;

                case 'E': // Edit Current Message
                    EditMessage();
                    mLink.Lines = 0;
                    mLink.dispose();
                    same = FALSE;
                    pipe2ansi((char *)"|CS");
                    _mnuf.choice = 0;
                    break;

                case 'A': // Redisplay message Again.
                    mLink.Lines = 0;
                    mLink.dispose();
                    same = FALSE;
                    _mnuf.choice = 0;
                    break;

                case '?': // Help Screen with Commands
                    mLink.clearBox();
                    ansiPrintf(sANSI_HELP);
                    getkey(TRUE);
                    mLink.Lines = 0;
                    mLink.dispose();
                    same = FALSE;
                    pipe2ansi((char *)"|CS");
                    _mnuf.choice = 0;
                    break;


                case ']': // Next Theme
                    mLink.Lines = 0;
                    mLink.dispose();
                    same = FALSE;
                    idx = thisuser->readertheme;
                    ++idx;
                    id1 = change_theme(idx);
                    // Reset Colors and Ansi to new Theme
                    if (id1 == TRUE) {
                        mLink.initReader(sTEXT_COLOR, sQUOTE_COLOR, sSYS_COLOR, sORIGIN_COLOR);
                        mLink.Top = tTop;
                        mLink.Bot = tBot;
                        pipe2ansi((char *)"|CS|CR|07FYI: |15You've switched Message Reader Themes.|CR|CR|PA");
                        _mnuf._premenu.clear();
                    } else {
                        // Reset Theme Back
                        change_theme(thisuser->readertheme);
                        pipe2ansi((char *)"|CS|CR|07FYI: |15You've hit the highest theme available. |CR|CR|PA");
                        _mnuf._premenu.clear();
                    }
                    pipe2ansi((char *)"|CS");
                    same = FALSE;
                    break;

                case '[': // Previous Theme
                    mLink.Lines = 0;
                    mLink.dispose();
                    same = FALSE;
                    idx = thisuser->readertheme;
                    if (idx != 0) {
                        --idx;
                    } else {
                        pipe2ansi((char *)"|CS|CR|07FYI: |15You've hit the lowest theme available. |CR|CR|PA");
                        pipe2ansi((char *)"|CS");
                        _mnuf._premenu.clear();
                        same = FALSE;
                        break;
                    }

                    id1 = change_theme(idx);
                    change_theme(thisuser->readertheme);

                    // Reset Colors and Ansi to new Theme
                    if (id1 == TRUE) {
                        mLink.initReader(sTEXT_COLOR, sQUOTE_COLOR, sSYS_COLOR, sORIGIN_COLOR);
                        mLink.Top = tTop;
                        mLink.Bot = tBot;
                        pipe2ansi((char *)"|CS|CR|07FYI: |15You've switched Message Reader Themes.|CR|CR|PA");
                        _mnuf._premenu.clear();
                    } else {
                        change_theme(thisuser->readertheme);
                        pipe2ansi((char *)"|CS|CR|07FYI: |15You've hit the lowest theme available. |CR|CR|PA");
                        _mnuf._premenu.clear();
                    }
                    pipe2ansi((char *)"|CS");
                    same = FALSE;
                    break;

                case 'S' : // Setup User Sig
                    SetupUserSig();
                    pipe2ansi((char *)"|CS");
                    mLink.Lines = 0;
                    mLink.dispose();
                    same = FALSE;
                    _mnuf.choice = 0;
                    break;

                default :
                    break;

                } // end of case
            }// end of Email If!
            else {
                // For Escaped Key Input is passed as Escped Key From Menu System
                // If EscPassing is Turned on in the Menu.
                ch = mString[0];
                switch (toupper(ch)) {
                case 'A':
                    mLink.box_pgup();
                    break;

                case 'B': // Scroll down 1 Line ( forced to paeg up / down for now)
                    mLink.box_pgdn();
                    break;

                default :
                    break;
                }
            }
        }
    }

    // Update History.
    hist_update(HIST_VIEWS,thisuser,Views);
    return rtnval;
}
