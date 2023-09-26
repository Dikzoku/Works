<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="java.io.*,java.util.*,java.sql.*"%>
<%@ page import="javax.servlet.http.*,javax.servlet.*" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/sql" prefix="sql"%>

<!DOCTYPE html>
<html>
   <head>
      <title>山东大学选课管理系统-管理端</title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" rel="stylesheet">
      <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
      <script src="https://oss.maxcdn.com/libs/respond.js/1.3.0/respond.min.js"></script>
   </head>
   <body>
   <% request.setCharacterEncoding("UTF-8"); %>
      <c:if test="${user==NULL}">
   	  	<script language='javascript'>
			window.location.href="index.jsp";
		</script>
   	  </c:if>
      <script src="https://code.jquery.com/jquery.js"></script>
      <script src="js/bootstrap.min.js"></script>
      
		<ul class="nav nav-tabs">
 		<li><a href="admin.jsp">个人信息</a></li>
  		<li class="active"><a href="admin_students.jsp">学生信息</a></li>
  		<li><a href="admin_teachers.jsp">教师信息</a></li>
  		<li><a href="admin_courses.jsp">课程信息</a></li>
  		<li><a href="admin_departments.jsp">院系信息</a></li>
  		<li style="float:right"><a href="logout.jsp">退出登录</a></li>
		</ul>
		
	<sql:setDataSource var="snapshot" driver="com.mysql.cj.jdbc.Driver"
     url="jdbc:mysql://localhost:3306/dikzoku?useUnicode=true&serverTimezone=UTC&characterEncoding=utf-8"
     user="root"  password="123456"/>
     
     <sql:update dataSource="${snapshot}" var="result">
		UPDATE student
		SET name=?<sql:param value="${param.name}" />,
			sex=?<sql:param value="${param.sex}" />,
			age=?<sql:param value="${param.age}" />,
			phone=?<sql:param value="${param.phone}" />,
			mail=?<sql:param value="${param.mail}" />,
			password=?<sql:param value="${param.password}" />,
			card_id=?<sql:param value="${param.card_id}" />,
			mid=?<sql:param value="${param.mid}" />,
			classid=?<sql:param value="${param.classid}" />
		WHERE student.sid = ? <sql:param value="${param.sid}" />;
	</sql:update>
	
     	<script language='javascript'>
			window.location.href="admin_students.jsp";
		</script>
     
   </body>
</html>