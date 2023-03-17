/*==============================================================*/
/* DBMS name:      PostgreSQL 9.x                               */
/* Created on:     23.11.2022 16:20:49                          */
/*==============================================================*/

/*==============================================================*/
/* Table: City                                                  */
/*==============================================================*/
create table City (
   id_city              INT4                 not null,
   id_coumtry           INT4                 not null,
   name_city            VARCHAR(150)         not null,
   constraint PK_CITY primary key (id_city)
);

/*==============================================================*/
/* Index: City_PK                                               */
/*==============================================================*/
create unique index City_PK on City (
id_city
);

/*==============================================================*/
/* Index: belongs_FK                                            */
/*==============================================================*/
create  index belongs_FK on City (
id_coumtry
);

/*==============================================================*/
/* Table: Client                                                */
/*==============================================================*/
create table Client (
   id_client            INT4                 not null,
   FIO_client           VARCHAR(120)         not null,
   number_client        CHAR(11)             not null,
   gender_client        VARCHAR(10)          null,
   pasport_client       CHAR(10)             not null,
   login_client         VARCHAR(50)          not null,
   pass_client          CHAR(50)             not null,
   constraint PK_CLIENT primary key (id_client)
);

/*==============================================================*/
/* Index: Client_PK                                             */
/*==============================================================*/
create unique index Client_PK on Client (
id_client
);

/*==============================================================*/
/* Table: Country                                               */
/*==============================================================*/
create table Country (
   id_coumtry           INT4                 not null,
   name_country         VARCHAR(50)          not null,
   constraint PK_COUNTRY primary key (id_coumtry),
   constraint AK_IDENTIFIER_1_COUNTRY unique (id_coumtry)
);

/*==============================================================*/
/* Index: Country_PK                                            */
/*==============================================================*/
create unique index Country_PK on Country (
id_coumtry
);

/*==============================================================*/
/* Table: Hotels                                                */
/*==============================================================*/
create table Hotels (
   id_hotel             INT4                 not null,
   id_city              INT4                 not null,
   name_hotel           VARCHAR(50)          not null,
   class_hotel          INT4                 not null,
   constraint PK_HOTELS primary key (id_hotel)
);

/*==============================================================*/
/* Index: Hotels_PK                                             */
/*==============================================================*/
create unique index Hotels_PK on Hotels (
id_hotel
);

/*==============================================================*/
/* Index: is_located_FK                                         */
/*==============================================================*/
create  index is_located_FK on Hotels (
id_city
);

/*==============================================================*/
/* Table: Meneger                                               */
/*==============================================================*/
create table Meneger (
   id_manager           INT4                 not null,
   FIO_manager          VARCHAR(120)         not null,
   number_manager       CHAR(11)             not null,
   gender_manager       VARCHAR(10)          null,
   post_manager         VARCHAR(50)          not null,
   login_manager        CHAR(50)             not null,
   pass_manager         CHAR(50)             not null,
   constraint PK_MENEGER primary key (id_manager)
);

/*==============================================================*/
/* Index: Meneger_PK                                            */
/*==============================================================*/
create unique index Meneger_PK on Meneger (
id_manager
);

/*==============================================================*/
/* Table: Ride                                                  */
/*==============================================================*/
create table Ride (
   id_order             INT4                 not null,
   id_client            INT4                 not null,
   id_manager           INT4                 not null,
   id_tour              INT4                 not null,
   date_order           DATE                 not null,
   constraint PK_RIDE primary key (id_order)
);

/*==============================================================*/
/* Index: Ride_PK                                               */
/*==============================================================*/
create unique index Ride_PK on Ride (
id_order
);

/*==============================================================*/
/* Index: register_FK                                           */
/*==============================================================*/
create  index register_FK on Ride (
id_manager
);

/*==============================================================*/
/* Index: include_tour_ride_FK                                  */
/*==============================================================*/
create  index include_tour_ride_FK on Ride (
id_tour
);

/*==============================================================*/
/* Index: buy_FK                                                */
/*==============================================================*/
create  index buy_FK on Ride (
id_client
);

/*==============================================================*/
/* Table: Tour                                                  */
/*==============================================================*/
create table Tour (
   id_tour              INT4                 not null,
   id_hotel             INT4                 not null,
   id_city              INT4                 not null,
   id_transport         INT4                 not null,
   sale_tour            NUMERIC(8,2)         not null,
   name_tour            VARCHAR(150)         not null,
   description_tour     VARCHAR(1)           null,
   date_start_tour      DATE                 not null,
   date_end_tour        DATE                 not null,
   constraint PK_TOUR primary key (id_tour)
);

/*==============================================================*/
/* Index: Tour_PK                                               */
/*==============================================================*/
create unique index Tour_PK on Tour (
id_tour
);

/*==============================================================*/
/* Index: include_transport_tour_FK                             */
/*==============================================================*/
create  index include_transport_tour_FK on Tour (
id_transport
);

/*==============================================================*/
/* Index: in_which_city_FK                                      */
/*==============================================================*/
create  index in_which_city_FK on Tour (
id_city
);

/*==============================================================*/
/* Index: in_which_hotel_FK                                     */
/*==============================================================*/
create  index in_which_hotel_FK on Tour (
id_hotel
);

/*==============================================================*/
/* Table: Transport                                             */
/*==============================================================*/
create table Transport (
   id_transport         INT4                 not null,
   type_transport       VARCHAR(50)          not null,
   constraint PK_TRANSPORT primary key (id_transport)
);

/*==============================================================*/
/* Index: Transport_PK                                          */
/*==============================================================*/
create unique index Transport_PK on Transport (
id_transport
);

alter table City
   add constraint FK_CITY_BELONGS_COUNTRY foreign key (id_coumtry)
      references Country (id_coumtry)
      on delete restrict on update restrict;

alter table Hotels
   add constraint FK_HOTELS_IS_LOCATE_CITY foreign key (id_city)
      references City (id_city)
      on delete restrict on update restrict;

alter table Ride
   add constraint FK_RIDE_BUY_CLIENT foreign key (id_client)
      references Client (id_client)
      on delete restrict on update restrict;

alter table Ride
   add constraint FK_RIDE_INCLUDE_T_TOUR foreign key (id_tour)
      references Tour (id_tour)
      on delete restrict on update restrict;

alter table Ride
   add constraint FK_RIDE_REGISTER_MENEGER foreign key (id_manager)
      references Meneger (id_manager)
      on delete restrict on update restrict;

alter table Tour
   add constraint FK_TOUR_IN_WHICH__CITY foreign key (id_city)
      references City (id_city)
      on delete restrict on update restrict;

alter table Tour
   add constraint FK_TOUR_IN_WHICH__HOTELS foreign key (id_hotel)
      references Hotels (id_hotel)
      on delete restrict on update restrict;

alter table Tour
   add constraint FK_TOUR_INCLUDE_T_TRANSPOR foreign key (id_transport)
      references Transport (id_transport)
      on delete restrict on update restrict;

