set names utf8;
#初始化数据库
drop database if exists `goatdb`;
create database goatdb;
use goatdb;
#羊舍
create table houseInfo(houseId varchar(100) primary key);
#奶山羊信息表
create table goatInfo(id int primary key auto_increment, goatId varchar(40) not null unique,houseId varchar(100) not null, weight float, inTime datetime, outTime datetime);
#设备信息表
create table deviceInfo(id  int primary key auto_increment,deviceId varchar(40) not null unique,deviceState varchar(20), inTime datetime);
#绑定信息表
create table bindingInfo(bindingId int primary key auto_increment,goatId varchar(40) not null unique, deviceId varchar(40) not null unique);
#路由设备表
create table routerInfo(id int primary key auto_increment,deviceId varchar(40) not null unique,deviceState varchar(20),inTime datetime);
#运动数据表
create table sportData(id int primary key auto_increment,goatId varchar(40) not null,datatimem varchar(20) not null,sportx varchar(20) not null,sporty varchar(20) not null, sportz varchar(20) not null,anglex varchar(20),angley varchar(20),anglez varchar(20),status varchar(40));
#羊舍数据表
create table houseData(id int primary Key auto_increment,houseId varchar(100) not null,datatimem varchar(20) not null,wendu varchar(20),anqi varchar(20),shidu varchar(20),eryang varchar(20));
#外键约束
alter table goatInfo add constraint fk_houseId foreign key(houseId) references houseInfo(houseId) on delete cascade on update cascade;
alter table bindingInfo add constraint fk_goatId foreign key(goatId) references goatInfo(goatId) on delete cascade on update cascade;
alter table bindingInfo add constraint fk_deviceId foreign key(deviceId) references deviceInfo(deviceId) on delete cascade on update cascade;

#触发器
delimiter ||
#create trigger bf_binding before insert
#on bindingInfo for each row
#begin
#  delete from bindingInfo where goatId = NEW.goatId;
#  delete from bindingInfo where deviceId = NEW.deviceId;
#end||
create trigger af_binding after insert
on bindingInfo for each row
begin
  update deviceInfo set deviceState = '已绑定' where deviceId = NEW.deviceId;
end||

create trigger af_binding_update after update
on bindingInfo for each row
begin
  update deviceInfo set deviceState = '闲置' where deviceId = OLD.deviceId;
  update deviceInfo set deviceState = '已绑定' where deviceId = NEW.deviceId;
end||

#create trigger af_device_update after update
#on deviceInfo for each row
#begin
#  if NEW.deviceState = '故障' then
#  delete from bindingInfo where deviceId = NEW.deviceId;
#  end if;
#end||

create trigger bf_del_deivce before delete
on goatInfo for each row
begin
  update deviceInfo set deviceState = '闲置' where deviceInfo.deviceId in (select bindingInfo.deviceId from bindingInfo where bindingInfo.goatId = old.goatId);
end||

create trigger bf_del_binding before delete
on bindingInfo for each row
begin
  update deviceInfo set deviceState = '闲置' where deviceId = old.deviceId;
end||

create trigger bf_insert_sportData before insert
on sportData for each row
begin
  set @tempGoatId = (select goatId from bindingInfo where deviceId = NEW.goatId);
  if(@tempGoatId is not null) then
    set NEW.goatId = @tempGoatId;
  end if;
end||

create trigger bf_insert_housetData before insert
on houseData for each row
begin
  #set @tempHouseId = (select houseId from houseBindingInfo where routerId = NEW.houseId);
  set @tempHouseId = (select a.houseId  from goatInfo a left join bindingInfo b on a.goatId = b.goatId where b.deviceId = NEW.houseId);
  if(@tempGoatId is not null) then
    set NEW.houseId = @tempHouseId;
  end if;
end||


delimiter ;
