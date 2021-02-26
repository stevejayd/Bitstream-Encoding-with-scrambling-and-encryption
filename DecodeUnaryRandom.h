

//***************************** DECODEING ********************************
void DecodeUnaryRandom(std::string& FileName)
{

    unsigned int Previous_bufindex = 0, NumberOfUnaryBits = 0, i = 0, j = 0, k = 0, Bit_Index_For_Byte = 0, ii = 0, Kbytes = 0;
    unsigned int OriginalVArray[400], OriginalRArray[400], RandIndex[400], VArray[400], RArray[400], SizeChunk[400], ShuffleArray[400][2];

    unsigned int Total_Bits = 0, BitCount = 0, kk = 0, BitsLeft, firstone = 0, Size = 0;
    unsigned  int BytesFromInputLoop = 0, NumberBytes = 0, NumberBits = 0, size = 0;
    unsigned char xin = 0, XinLow = 0, XinHigh = 0, alternate = 0;
    unsigned int ctemp = 0, R = 0, tempscheme = 0;
    unsigned int v1 = 0, v2 = 0, r1 = 0, r2 = 0, PlainTextMemorySize = 0, NumberOfPlainTextBits = 0, ArrayIndex = 0, rtemp = 0, V = 0, BitsEncoded = 0;
    unsigned int ChunkSize = 0, ChunkCount = 0, NewChunkSize = 0, ByteMask = 0xffff;
    //
    unsigned char Left_Over = 0, ByteTemp = 0, NextByte = 0, CharTemp = 0, vtemp = 0, Random = 0;
    unsigned char PreviousNull = 1, temp = 0, Alternate = 0, AddNulls = 0x00;
    unsigned char Mask[8], BytesToFile[1000];
    unsigned char DecodeMask = 0, HighByte = 0, LowByte = 0 ;
    unsigned char HeaderLength = 16;// information on data sent.

    bool TestBit, One = 1, TempTest = 0, Vstart = 0, SwapChunks = 0, krandom = 0, XorBits = 0;
    //**************************************************** Trailer ************************
    unsigned int TrailerLength = 24;
    std::bitset<4>Nulls1("0011");
    std::bitset<4>Nulls0("1100");
    std::string ConsoleInput;
    std::string TempString;
    //***************************************** Bits *************************
    std::bitset<5000>PlainTextBiits; // the max for sum of vs and rs are 512
    PlainTextMemorySize = PlainTextBiits.size();
    std::bitset<10000>EncodedBits;
    std::bitset<256>ChunkBits;// largest chunk would be this size
    std::bitset<10000>DecodedBits;
    std::bitset <8>TempBits;
    std::bitset <10000>EncryptBits;
    //std::string FileName = "EncodedUnaryBits1.bin";
    //*******************************************************************
    if (FileName=="")FileName = "EncodedUnaryBits1.bin";
    //********************************************************************
    std::cout << "\n        Random Swap Chunks ? .... Enter Y or N  ";
    std::cin >> TempString;
    std::cout << " \n";

     //************************************************* Read File **************************************

      std::ifstream input(FileName, std::ios::binary);

      // copies all data into "buffer"
      std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});
      myfile.close();
      //*************************************************************************************
      i = buffer[0];// highbyte
      LowByte = buffer[1];
      
      NumberBytes = i<<= 8;
      NumberBytes = NumberBytes + LowByte;
      SwapChunks = buffer[2];
      XorBits = buffer[3];
 
      std::cout <<  "  Number of Bytes = " << NumberBytes << "  Number of Bits = " << NumberOfUnaryBits<<" \n";
      //************ Read bytes and converts to bits *********************
      for (i = 4;i < NumberBytes;i++)
      {
          CharTemp = buffer[i];
          DecodeMask = 0x80;
          for (ii = 0;ii < 8;ii++)
          { 
              TestBit = CharTemp & DecodeMask;
              if (TestBit) EncodedBits.set(BitCount);
              BitCount++;
              DecodeMask >>= 1;

          }
      }
      if (XorBits)
      {
          std::cout << " \n ********* This is the Encrypted Being Sent **************  Encrypt by  XOR ***************** \n\n\n";
          for (i = 0;i < NumberOfUnaryBits;i++)
          {
              if (EncryptBits.test(i) == 1) EncodedBits.flip(i);
              std::cout << EncodedBits.test(i);
          }
      }
      
      
    //NumberOfUnaryBits = EncodedBits.size();
    TestBit = EncodedBits.test(0);
    TempTest = TestBit;
    ChunkCount = 0;
    kk = 0;
    V = 1;
    BitCount = 0;
    Vstart = TestBit;
    // First bit in message
    while (BitCount < NumberOfUnaryBits)
    {
        TestBit = EncodedBits.test(BitCount);
        if (TestBit != Vstart)
        {
            // a change

            // vr,vr,vr....chunks size is the begin ov the V to the begin of r

            if (V == 1) {
                VArray[ChunkCount] = kk;// for "A" there would be 66 ones (Array index from 0 to 65)

                V = 0;// WE HAVE GOTTEN A V
                R = 1;
                SizeChunk[ChunkCount] = kk;
                kk = 0;
                Vstart = TestBit;
            }
            else
            {
                RArray[ChunkCount] = kk;// -VArray[ChunkCount];

                ChunkCount++;
                R = 0;// We have gotten an R
                // so the first zero (assuming v's were ones)
                V = 1;
                ii = kk;
                kk = 0;

                Vstart = TestBit;
            }
            !Vstart;




        };
        kk++;
        BitCount++;
    };

    // finsihed and never found and R or V fill in remainder with kk-1;
    //****************************************************************************************
   
  
    if (R == 1) RArray[ChunkCount] = kk;

    std::cout << "\n                      This is the reconstructed RV Arrays from the encoded stream \n";
    for (i = 0;i < ChunkCount;i++) {

        std::cout << i << "  V" << i << "= " << VArray[i] << "     ";

        std::cout << " R" << i << "= " << RArray[i];

        std::cout << "\n";

    };

  // **************************************** Now Retrieve ascii message **************

    

    std::cout << "\n                   Run throug the chunks and re-assemble the original bitstream \n";
    std::cout << " \n             First Step is to dscramble text bt un swapping the chunks .. if it was does done     ";
    CharTemp = 0;
    Kbytes = 0;


    //*********************************** Unswap **************************
   
    // Clear arrays
    for (i = 0;i < 200;i++) 
    {
        OriginalVArray[i] = 0;
        OriginalRArray[i] = 0;
    }
   
        // the first one receuved is VArray[0] which is then placed in NUMS[i], if Nums[0]=3. then it is placed in the third one in or i=2
        for (i = 0;i <= ChunkCount;i++) {
            ii = i;
            if(SwapChunks)   ii=nums[i];
            OriginalVArray[ii] = VArray[i];
            OriginalRArray[ii] = RArray[i];
        }
        std::cout << "\n **********     Descrambled Array *****************  \n";
        for (i = 0;i <= ChunkCount;i++) {

            std::cout << " V" << i << "= " << OriginalVArray[i] << "     ";

            std::cout << " R" << i << "= " << OriginalRArray[i];

            std::cout << "\n";

        };
          
  
   
    std::cout << "        Decoded  bit stream ********************  \n";
    for (i = 0;i <= 200;i++) SizeChunk[i] = 0;
    BitCount = 0;// place bits from 0 to7 for bytes etc.
    DecodedBits.reset();
        // run through Varrays and assemple bytes
    //                                                       012     345    678         9
    //"AB " 01000001 01000010 break into chunks size =3  ,   010     000    010         100         001         0 
    //***************                                      R=2,V=3 V=1,R=4   R=2,V=3    R=1,V=1    R=3.V=2   R=2.V=1
    // Calculate size of chunks 
    for (i = 0;i <= ChunkCount;i++)
    {
        SizeChunk[i] = 0;
        rtemp = OriginalRArray[i] - 1;
        vtemp = OriginalVArray[i] - 1;

        // begin at BitCount to place next
        // find top bit of vtemp
        DecodeMask = 128; //0b10000000
        if (vtemp == 0)// there are only zeroes
        {
            SizeChunk[i] = rtemp;
        }
        else
        {
            for (ii = 0;ii < 8;ii++)
            {
                temp = (DecodeMask & vtemp);// find  the first one
                TestBit = bool(temp);
                if (TestBit)
                {
                    SizeChunk[i] = 8 - ii + rtemp;
                    break;
                }
                DecodeMask >>= 1;
            };
        };
       
        CharTemp = vtemp;
        TempTest = 0;
        std::cout << " V" << i << " =" << OriginalVArray[i] << "  R" << i << " =" << OriginalRArray[i] << "  Size = " << SizeChunk[i] << "  \n";
    };
    std::cout << "  Now decode the RV arrays into bytes   \n";
    CharTemp = 0x00;
    for (i = 0;i <= ChunkCount;i++)
    {
        TempTest = 0;
        rtemp = OriginalRArray[i] - 1;
        vtemp = OriginalVArray[i] - 1;
        j = SizeChunk[i];
        DecodeMask = 0x01;
        DecodeMask <<= (j - 1);
        // first we add the leading zeros
        for (kk = 0;kk < rtemp;kk++)
        {
            DecodedBits.reset(BitCount);
            BitCount++; // next bit position to test
            DecodeMask >>= 1;
        }
        TempTest = 0;
        if (vtemp > 0)
        {
            // run through Varrays and assemple bytes
//                                                       012     345    678         9
//"AB " 01000001 01000010 break into chunks size =3  ,   010     000    010         100         001         0 
//***************                                      R=2,V=3 V=1,R=4   R=2,V=3    R=1,V=1    R=3.V=2   R=2.V=1
            for (ii = 0;ii < j;ii++)
            {
                if (DecodeMask < 1) break;
                temp = DecodeMask & vtemp;// find  the first one
                 DecodeMask >>= 1;
                TestBit = bool(temp);
                if (TempTest)// found the first one
                {

                    TempTest = 1;
                    // now run throught bits and add them
                  
                    if (TestBit) DecodedBits.set(BitCount, TestBit);
                    BitCount++;

                }
                else
                {
                    if (TestBit) TempTest = 1;
                    DecodedBits.set(BitCount, TestBit);// start of V
                    BitCount++;
                }
                
                
            };
        }
       // BitCount++;
    };
        


  
 
    std::cout << "  Message was \n";

    kk = 0;ii = 0;
       while(ii<BitCount)
       {
           CharTemp = 0;
           kk = 0x80;
           // the first bit is the MSB 0x80 or 128;
           for (i = 0;i < 8;i++)
           {
               TestBit = DecodedBits.test(ii);
               if (TestBit)CharTemp = CharTemp + kk;
               kk >>= 1;
                  
               ii++;
           }
           std::cout << CharTemp;
           
        };
  
       std::cout << " \n ************* MESSAGE COMPLETE *****************\n ";
}
       
  
















