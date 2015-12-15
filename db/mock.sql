-- MySQL dump 10.13  Distrib 5.5.46, for debian-linux-gnu (armv7l)
--
-- Host: localhost    Database: mock
-- ------------------------------------------------------
-- Server version	5.5.46-0+deb7u1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `pid_metadata`
--

DROP TABLE IF EXISTS `pid_metadata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pid_metadata` (
  `pid` tinyint(4) NOT NULL,
  `name` varchar(255) NOT NULL,
  `units` varchar(16) DEFAULT NULL,
  PRIMARY KEY (`pid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pid_metadata`
--

LOCK TABLES `pid_metadata` WRITE;
/*!40000 ALTER TABLE `pid_metadata` DISABLE KEYS */;
INSERT INTO `pid_metadata` VALUES (0,'Supported PIDS',NULL),(1,'Status since last clearing',NULL),(6,'Short term fuel - Bank 1','%'),(7,'Long term fuel - Bank 1','%'),(8,'Short term fuel - Bank 2','%'),(9,'Long term fuel - Bank 2','%'),(10,'Fuel Pressure','kPa'),(11,'Intake Manifold Pressure','kPa'),(12,'Engine RPM','rpm'),(13,'Vehicle Speed','km/h'),(14,'Timing Advance','degrees'),(15,'Intake Air Temp.','oC'),(16,'MAF Air Flow','grams/sec'),(17,'Throttle Position','%'),(31,'Engine Run Time','sec');
/*!40000 ALTER TABLE `pid_metadata` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-12-15 15:48:04
