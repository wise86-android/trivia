package com.adaptionsoft.games.trivia

import com.adaptionsoft.games.trivia.runner.runGame
import org.junit.Assert
import org.junit.Test
import java.io.ByteArrayOutputStream
import java.io.PrintStream
import java.nio.ByteBuffer
import java.nio.charset.Charset
import java.nio.file.Files
import java.nio.file.Paths

class GoldenMasterTest {

    @Test
    @Throws(Exception::class)
    fun goldenMasterMatchesMultipleTriviaRunsOutput() {
        if (!Files.exists(GOLDEN_MASTER_PATH)) {
            writeGoldenMaster()
        }

        val goldenMasterContent = readGoldenMaster()
        val outputStream = ByteArrayOutputStream()
        runTrivia(PrintStream(outputStream))

        Assert.assertEquals(goldenMasterContent, outputStream.toString())
    }

    @Throws(Exception::class)
    private fun writeGoldenMaster() {
        val output = PrintStream(GOLDEN_MASTER_PATH.toFile())
        runTrivia(output)
    }

    @Throws(Exception::class)
    private fun readGoldenMaster(): String {
        val bytes = Files.readAllBytes(GOLDEN_MASTER_PATH)
        return Charset.defaultCharset().decode(ByteBuffer.wrap(bytes)).toString()
    }

    private fun runTrivia(output: PrintStream) {
        System.setOut(output)
        for (i in 1..RUNS) {
            runGame(i)
        }
        output.flush()
        System.setOut(System.out)
    }

    companion object {
        private val GOLDEN_MASTER_PATH = Paths.get("golden-master.out")
        private val RUNS = 100
    }
}
