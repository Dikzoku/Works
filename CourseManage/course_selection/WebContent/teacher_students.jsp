<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="java.io.*,java.util.*,java.sql.*"%>
<%@ page import="javax.servlet.http.*,javax.servlet.*" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/sql" prefix="sql"%>

<!DOCTYPE html>
<html>
   <head>
      <title>山东大学选课管理系统-教师端</title>
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
 		<li><a href="teacher.jsp">个人信息</a></li>
  		<li><a href="teacher_teach.jsp">授课信息</a></li>
  		<li><a href="teacher_enter_scores.jsp">成绩录入</a></li>
  		<li class="active"><a href="teacher_students.jsp">学生名单</a></li>
  		<li style="float:right"><a href="logout.jsp">退出登录</a></li>
		</ul>
		
	<sql:setDataSource var="snapshot" driver="com.mysql.cj.jdbc.Driver"
     url="jdbc:mysql://localhost:3306/dikzoku?useUnicode=true&serverTimezone=UTC&characterEncoding=utf-8"
     user="root"  password="123456"/>
     
    <sql:query dataSource="${snapshot}" var="teached">
     	select tid,course.cid,cname,ccredit,ctime from teachcourse,course 
     	where tid=?<sql:param value="${user}" />
     		and teachcourse.cid=course.cid
     </sql:query>
     <div class="container" style="width:500px">
     <form name="input" action="teacher_students.jsp" method="POST">
     	<select name="courseid" class="form-control" style="text-align:center">
     	 <c:forEach var="row" items="${teached.rows}">
     	 <c:if test="${row.cid==param.courseid}">
     	  <option value="${row.cid}" selected="selected"><c:out value="${row.cname}" />(<c:out value="${row.cid}"/>)</option>
     	  </c:if>
     	  <c:if test="${row.cid!=param.courseid}">
     	  <option value="${row.cid}"><c:out value="${row.cname}"/>(<c:out value="${row.cid}"/>)</option>
     	  </c:if>
     	 </c:forEach>
   		</select>
     	<button type="submit" class="btn btn-default" style="float:right;">选择该授课班级</button>
     </form>
     </div>
     
     <sql:query dataSource="${snapshot}" var="teached_students">
     	select * from selectcourse,student
     	where cid=?<sql:param value="${param.courseid}" />
     		and selectcourse.sid=student.sid
     </sql:query>
     
<div class="container">
 <form name="input" action="teacher_students.jsp" method="POST">
 	<input type="hidden" name="courseid" value="${param.courseid}"/>
 	<input type="text" name="sid" placeholder="请输入学生学号" value="${param.sid}"/>
 	<input type="submit" value="搜索学生" class="btn btn-default"/>
 </form>                            
	<table class="table table-hover">
		<thead>
			<h4>学生信息</h4>
			<td><c:out value="学号"/></td>
			<td><c:out value="姓名"/></td>
			<td><c:out value="性别"/></td>
			<td><c:out value="年龄"/></td>
			<td><c:out value="手机号"/></td>
			<td><c:out value="邮箱"/></td>
			<td><c:out value="成绩"/></td>
		</thead>
		<tbody>
		 <c:forEach var="row" items="${teached_students.rows}">
		 <c:if test="${param.sid==row.sid||param.sid==null||param.sid==''}">
		  <tr>
   		   <td><c:out value="${row.sid}"/></td>
   		   <td><c:out value="${row.name}"/></td>
   		   <td><c:out value="${row.sex}"/></td>
   		   <td><c:out value="${row.age}"/></td>
   		   <td><c:out value="${row.phone}"/></td>
   		   <td><c:out value="${row.mail}"/></td>
   		   <td><c:out value="${row.score}"/></td>
   		  </tr>
   		  </c:if>
		 </c:forEach>
		</tbody>
	</table>
</div>
     
   </body>
</html>