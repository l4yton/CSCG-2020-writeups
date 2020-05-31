bool __fastcall ServerManager__sendData(ServerManager_o *this, System_Byte_array *pkt)
{
  void *v2; // rdx
  int v3; // ecx
  int v4; // er8
  char v5; // r9
  System_Byte_array *v6; // r15
  ServerManager_o *v7; // r14
  __int64 v8; // r12
  System_Random_o *v9; // rdi
  int v10; // ebx
  System_Random_o *v11; // rdi
  char v12; // al
  unsigned int v13; // edx
  unsigned int v14; // esi
  __int64 v15; // rcx
  unsigned __int64 v16; // rax
  __int64 v17; // rdi
  __int64 v18; // rbx
  System_Net_Sockets_UdpClient_o *v19; // rdi
  __int64 v21; // rax
  __int64 v22; // rax
  __int64 v23; // rax
  __int64 v24; // rax
  __int64 v25; // rax
  __int128 v26; // [rsp+0h] [rbp-38h]

  v6 = pkt;
  v7 = this;
  if ( !byte_1135A52 )
  {
    this = (ServerManager_o *)(&stru_2457 + 16);
    sub_322830(9319, (int)pkt, v2, v3, v4, v5);
    byte_1135A52 = 1;
  }
  if ( !pkt )
    sub_3230B0(this);
  v8 = il2cpp_array_new_specific_0(Class_byte__, (unsigned int)(LODWORD(pkt->max_length) + 2));
  v9 = v7->rand;
  if ( !v9 )
    sub_3230B0(0LL);
  LOBYTE(v10) = ((__int64 (__fastcall *)(System_Random_o *, __int64, __int64, void *))v9->klass->vtable._5_Next.methodPtr)(
                  v9,
                  1LL,
                  255LL,
                  v9->klass->vtable._5_Next.method);
  if ( !v8 )
    sub_3230B0(v9);
  if ( !*(_DWORD *)(v8 + 24) )
  {
    v26 = 0LL;
    v24 = sub_2BC6E0(*(_QWORD *)&qword_113C4B0, "System", "IndexOutOfRangeException", &v26);
    sub_322D10(v24, 0LL);
  }
  *(_BYTE *)(v8 + 32) = v10;
  v11 = v7->rand;
  if ( !v11 )
    sub_3230B0(0LL);
  v12 = ((__int64 (__fastcall *)(System_Random_o *, __int64, __int64, void *))v11->klass->vtable._5_Next.methodPtr)(
          v11,
          1LL,
          255LL,
          v11->klass->vtable._5_Next.method);
  if ( (unsigned int)*(_QWORD *)(v8 + 24) <= 1 )
  {
    v26 = 0LL;
    v25 = sub_2BC6E0(*(_QWORD *)&qword_113C4B0, "System", "IndexOutOfRangeException", &v26);
    sub_322D10(v25, 0LL);
  }
  v13 = *(_QWORD *)(v8 + 24);
  *(_BYTE *)(v8 + 33) = v12;
  if ( (int)pkt->max_length > 0 )
  {
    v14 = pkt->max_length;
    v15 = 0x200000000LL;
    v16 = 0LL;
    do
    {
      if ( v16 >= v14 )
      {
        v26 = 0LL;
        v21 = sub_2BC6E0(*(_QWORD *)&qword_113C4B0, "System", "IndexOutOfRangeException", &v26);
        sub_322D10(v21, 0LL);
      }
      v17 = v16 + 2;
      if ( v16 + 2 >= v13 )
      {
        v26 = 0LL;
        v22 = sub_2BC6E0(*(_QWORD *)&qword_113C4B0, "System", "IndexOutOfRangeException", &v26);
        sub_322D10(v22, 0LL);
      }
      *(_BYTE *)(v8 + (v15 >> 32) + 32) = v10 ^ v6->m_Items[v16];
      if ( (unsigned int)*(_QWORD *)(v8 + 24) <= 1 )
      {
        v26 = 0LL;
        v23 = sub_2BC6E0(*(_QWORD *)&qword_113C4B0, "System", "IndexOutOfRangeException", &v26);
        sub_322D10(v23, 0LL);
      }
      v13 = *(_QWORD *)(v8 + 24);
      v18 = (unsigned __int8)v10 + (unsigned int)*(unsigned __int8 *)(v8 + 33);
      v10 = v18 + ((unsigned __int64)(2155905153LL * v18) >> 39);
      v14 = v6->max_length;
      v15 += 0x100000000LL;
      ++v16;
    }
    while ( v17 - 1 < (int)v14 );
  }
  v19 = v7->client;
  if ( !v19 )
    sub_3230B0(0LL);
  System_Net_Sockets_UdpClient__Send(v19, (System_Byte_array *)v8, v13);
  return 1;
}
