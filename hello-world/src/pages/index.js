import React from "react"
import Layout from "../components/layout"
import Largebutton from "../components/button"
import containerStyles from "../components/container.module.css"

export default function Home() {
  return (
    <Layout>
      <h1>Hi! I'm building a fake Gatsby site as part of a tutorial!</h1>
      <p>
        What do I like to do? Lots of course but definitely enjoy building
        websites.
      </p>

      <a className={containerStyles.linktest} href="https://example.com" target="_blank" rel="noopener noreferrer"> Herro </a>
      <a className={containerStyles.linktestGreen} href="https://example.com" target="_blank" rel="noopener noreferrer"> Herro </a>


    </Layout>


  );
}