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
  		<li class="active"><a href="teacher_teach.jsp">授课信息</a></li>
  		<li><a href="teacher_enter_scores.jsp">成绩录入</a></li>
  		<li><a href="teacher_students.jsp">学生名单</a></li>
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
     
<div class="container">  
 <form name="input" action="teacher_teach.jsp" method="POST">
 	<input type="text" name="cid" placeholder="请输入课序号" value="${param.cid}"/>
 	<input type="submit" value="搜索课程" class="btn btn-default"/>
 </form>                        
	<table class="table table-hover">
		<thead>
			<h4>所授课程</h4>
			<tr>
				<td>课程号</td>
				<td>课程名</td>
				<td>学分</td>
				<td>学时</td>
			</tr>
		</thead>
		<tbody>
		 <c:forEach var="row" items="${teached.rows}">
		 <c:if test="${param.cid==row.cid||param.cid==null||param.cid==''}">
		  <tr>
   		   <td><c:out value="${row.cid}"/></td>
   		   <td><c:out value="${row.cname}"/></td>
   		   <td><c:out value="${row.ccredit}"/></td>
   		   <td><c:out value="${row.ctime}"/></td>
   		  </tr>
   		  </c:if>
		 </c:forEach>
		</tbody>
	</table>
</div>
     
   </body>
</html>