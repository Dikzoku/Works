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
  		<li><a href="admin_students.jsp">学生信息</a></li>
  		<li class="active"><a href="admin_teachers.jsp">教师信息</a></li>
  		<li><a href="admin_courses.jsp">课程信息</a></li>
  		<li><a href="admin_departments.jsp">院系信息</a></li>
  		<li style="float:right"><a href="logout.jsp">退出登录</a></li>
		</ul>
		
	<sql:setDataSource var="snapshot" driver="com.mysql.cj.jdbc.Driver"
     url="jdbc:mysql://localhost:3306/dikzoku?useUnicode=true&serverTimezone=UTC&characterEncoding=utf-8"
     user="root"  password="123456"/>
     
     <sql:query dataSource="${snapshot}" var="result">
     	select * from teacher
     </sql:query>
     
<div class="container">
			<h4>教师信息</h4>
 <form name="input" action="admin_teachers.jsp" method="POST">
 	<input type="text" name="qrytid" placeholder="请输入教师职工号" value="${param.qrytid}"/>
 	<input type="submit" value="搜索教师" class="btn btn-default"/>
 </form>
  <form name="input" action="admin_teachers.jsp" method="POST">
 	<input type="text" name="qrydid" placeholder="请输入学院编号" value="${param.qrydid}"/>
 	<input type="submit" value="搜索该学院教师" class="btn btn-default"/>
 </form>     
	<table class="table table-hover">
		<thead>
			<tr>
   		   		<td><c:out value="职工号"/></td>
   		   		<td><c:out value="姓名"/></td>
   		   		<td><c:out value="性别"/></td>
   		   		<td><c:out value="年龄"/></td>
   		   		<td><c:out value="电话"/></td>
   		   		<td><c:out value="邮箱"/></td>
   		   		<td><c:out value="身份证号"/></td>
   		   		<td><c:out value="所属学院编号"/></td>
   		   		<td><c:out value="密码"/></td>
		  	</tr>
		</thead>
		<tbody>
		 <c:forEach var="row" items="${result.rows}">
		 <c:if test="${param.qrydid==row.did||param.qrydid==null||param.qrydid==''}">
		 <c:if test="${param.qrytid==row.tid||param.qrytid==null||param.qrytid==''}">
		 <tr>
		 <form name="input" action="admin_teachers_upd.jsp" method="POST">
		 	<input type="hidden" name="thetid" value="${row.tid}"/>
   		   <td><c:out value="${row.tid}"/></td>
   		   <td><c:out value="${row.name}"/></td>
   		   <td><c:out value="${row.sex}"/></td>
   		   <td><c:out value="${row.age}"/></td>
   		   <td><c:out value="${row.phone}"/></td>
   		   <td><c:out value="${row.mail}"/></td>
   		   <td><c:out value="${row.card_id}"/></td>
   		   <td><c:out value="${row.did}"/></td>
   		   <td><c:out value="******"/></td>
   		   <td><button type="submit" class="btn btn-default">修改信息</button></td>
   		  </form>
   		  <form name="input" action="admin_teachers_del.jsp" method="POST">
   		  	<input type="hidden" name="thetid" value="${row.tid}"/>
   		  	<td><button type="submit" class="btn btn-default">删除信息</button></td>
   		  </form>
   		  <form name="input" action="admin_teachers_teach.jsp" method="POST">
   		  	<input type="hidden" name="tid" value="${row.tid}"/>
   		  	<input type="hidden" name="tname" value="${row.name}"/>
   		  	<td><button type="submit" class="btn btn-default">查看授课信息</button></td>
   		  </form>
   		   </tr>
   		   </c:if>
   		   </c:if>
		 </c:forEach>
		 	<form name="input" action="admin_teachers_ins.jsp" method="POST">
		 	<input type="hidden" name="thetid" value="${row.tid}"/>
		 		<tr>
		 		<td><input type="text" name="tid" placeholder="${row.tid}" value="${row.tid}" style="width:100px"/></td>
		 		<td><input type="text" name="name" placeholder="${row.name}" value="${row.name}" style="width:100px"/></td>
		 		<td><input type="text" name="sex" placeholder="${row.sex}" value="${row.sex}" style="width:100px"/></td>
		 		<td><input type="text" name="age" placeholder="${row.age}" value="${row.age}" style="width:100px"/></td>
		 		<td><input type="text" name="phone" placeholder="${row.phone}" value="${row.phone}" style="width:100px"/></td>
		 		<td><input type="text" name="mail" placeholder="${row.mail}" value="${row.mail}" style="width:100px"/></td>
		 		<td><input type="text" name="card_id" placeholder="${row.card_id}" value="${row.card_id}" style="width:100px"/></td>
		 		<td><input type="text" name="did" placeholder="${row.did}" value="${row.did}" style="width:100px"/></td>
		 		<td><input type="password" name="password"  value="${row.password}" style="width:100px"/></td>
   		    	<td><button type="submit" class="btn btn-default">插入信息</button></td>
   		    	</tr>
   		  </form>
		</tbody>
	</table>
	
</div>
     
     
   </body>
</html>