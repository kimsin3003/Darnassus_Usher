use darnassus;

drop database darnassus;

LOAD DATA LOCAL INFILE 'F://Dropbox//Project//DB Basic//Darnassus_Usher//buildings.csv'
INTO TABLE building FIELDS TERMINATED BY ',' ENCLOSED BY '"' LINES TERMINATED BY '\n';

LOAD DATA LOCAL INFILE 'F://Dropbox//Project//DB Basic//Darnassus_Usher//guest.csv'
INTO TABLE guest FIELDS TERMINATED BY "," ENCLOSED BY '"'
LINES TERMINATED BY '\n';

LOAD DATA LOCAL INFILE 'F://Dropbox//Project//DB Basic//Darnassus_Usher//item.csv'
INTO TABLE item FIELDS TERMINATED BY "," ENCLOSED BY '"'
LINES TERMINATED BY '\n';

LOAD DATA LOCAL INFILE 'F://Dropbox//Project//DB Basic//Darnassus_Usher//npc.csv'
INTO TABLE npc FIELDS TERMINATED BY "," ENCLOSED BY '"'
LINES TERMINATED BY '\n';

LOAD DATA LOCAL INFILE 'F://Dropbox//Project//DB Basic//Darnassus_Usher//region.csv'
INTO TABLE region FIELDS TERMINATED BY "," ENCLOSED BY '"'
LINES TERMINATED BY '\n';

select * from region;
select * from guest;

call insert_npc("메롱", "흑마", 2);


select * from npc;

delete from npc where id = 255;


select * from npc where name like '%그웬 암스테드%';

delete from npc where id >= 128;

select * from item;

insert into building (name, purpose) value("울부짖는 참나무1", "피난처");

select * from region where name = '%울부짖는 참나무%';

select * from building;

select * from item;

delete from item where NPC_id = 10 or NPC_id = 20;


set @item_name = '%가로날 도끼%';
select i.name, n.name, b.name, r.name 
        from item as i, npc as n, building as b, region as r 
        where i.NPC_id = n.id and n.Building_id = b.id and n.Region_id = r.id and i.name like @item_name;
        
call search_item(@item_name);


desc building;

desc region;


