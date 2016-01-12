-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema Darnassus
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema Darnassus
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `Darnassus` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci ;
USE `Darnassus` ;

-- -----------------------------------------------------
-- Table `Darnassus`.`Region`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Darnassus`.`Region` (
  `name` VARCHAR(45) NOT NULL COMMENT '',
  `description` VARCHAR(45) NULL COMMENT '',
  PRIMARY KEY (`name`)  COMMENT '')
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Darnassus`.`Building`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Darnassus`.`Building` (
  `name` VARCHAR(30) NOT NULL COMMENT '',
  `purpose` VARCHAR(45) NULL COMMENT '',
  `region_name` VARCHAR(45) NULL COMMENT '',
  PRIMARY KEY (`name`)  COMMENT '',
  INDEX `fk_Building_Region1_idx` (`region_name` ASC)  COMMENT '',
  CONSTRAINT `fk_Building_Region1`
    FOREIGN KEY (`region_name`)
    REFERENCES `Darnassus`.`Region` (`name`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Darnassus`.`NPC`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Darnassus`.`NPC` (
  `name` VARCHAR(45) NOT NULL COMMENT '',
  `role` VARCHAR(45) NULL COMMENT '',
  `Building_name` VARCHAR(30) NULL COMMENT '',
  `Region_name` VARCHAR(45) NOT NULL COMMENT '',
  PRIMARY KEY (`name`)  COMMENT '',
  INDEX `fk_NPC_Building1_idx` (`Building_name` ASC)  COMMENT '',
  INDEX `fk_NPC_Region1_idx` (`Region_name` ASC)  COMMENT '',
  CONSTRAINT `fk_NPC_Building1`
    FOREIGN KEY (`Building_name`)
    REFERENCES `Darnassus`.`Building` (`name`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_NPC_Region1`
    FOREIGN KEY (`Region_name`)
    REFERENCES `Darnassus`.`Region` (`name`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Darnassus`.`Item`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Darnassus`.`Item` (
  `name` VARCHAR(45) NOT NULL COMMENT '',
  `price` INT NULL COMMENT '',
  `NPC_name` VARCHAR(45) NULL COMMENT '',
  PRIMARY KEY (`name`)  COMMENT '',
  INDEX `fk_Item_NPC_idx` (`NPC_name` ASC)  COMMENT '',
  CONSTRAINT `fk_Item_NPC`
    FOREIGN KEY (`NPC_name`)
    REFERENCES `Darnassus`.`NPC` (`name`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Darnassus`.`Guest`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Darnassus`.`Guest` (
  `id` VARCHAR(45) NOT NULL COMMENT '',
  `Building_name` VARCHAR(30) NOT NULL COMMENT '',
  PRIMARY KEY (`id`)  COMMENT '',
  INDEX `fk_Guest_Building1_idx` (`Building_name` ASC)  COMMENT '',
  CONSTRAINT `fk_Guest_Building1`
    FOREIGN KEY (`Building_name`)
    REFERENCES `Darnassus`.`Building` (`name`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
